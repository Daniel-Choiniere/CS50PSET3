// Copies a BMP file
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage - check to make sure user is entering exactly four argumnets (the filename of this program, the resize factor, the infile, and the outfile)
    if (argc != 4)
    {
        // printf("%i\n", argc);
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
    }

    // change the input to a number so we can work with it
    // the resizeFactor we got from the user is the second argument
    int resizeFactor = atoi(argv[1]);

    // remember filenames
    // infile is the third argument
    char *infile = argv[2];
    // outfile is the fourth argument
    char *outfile = argv[3];

    // open input file as read only
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // get the width and height of the original image
    int ogWidth = bi.biWidth;
    // we need to get the absolute (positive number) of the height, because in some cases it will be negative and we want it to always be positive
    int ogHeight = abs(bi.biHeight);

    // intialize the height and width for the new file (calculte the new dimensions by multiplying by resizeFactor)
    int newWidth = bi.biWidth * resizeFactor;
    int newHeight = bi.biHeight * resizeFactor;

    // deal with padding if necessary
    // old padding
    int padding = (4 - (ogWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // new padding
    int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update the header info for the new file, chnage the bi.biHeight and bi.biWidh, etc. to be the updated parameters
    bi.biHeight = newHeight;
    bi.biWidth = newWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * abs(newHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // declare an array for storing the entire row to be written.
    RGBTRIPLE wholeRow[bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(ogHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < ogWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // creating the array by writing the pixel 'resizeFactor' number of times
            for (int k = 0; k < resizeFactor; k++)
            {
                wholeRow[k + (resizeFactor * j)] = triple;
            }
        }

        for (int j = 0; j < resizeFactor; j++)
        {
            // write out the built array 'resizeFactor' amount of times
            fwrite(wholeRow, sizeof(wholeRow), 1, outptr);

            // add the new padding back in if needed
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}