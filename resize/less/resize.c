// Copies a BMP file
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        // printf("%i\n", argc);
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
    }

    // change the input to a number so we can work with it
    int resizeFactor = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
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

    // printf("%d\n", bi.biWidth);
    // printf("%d\n", bi.biHeight);
    // printf("%d\n", bi.biSizeImage);
    // printf("%d\n", bf.bfSize);

    // get the width and height of the original image
    int ogWidth = bi.biWidth;
    int ogHeight = bi.biHeight;

    // intialize the height and width for the new file
    int newWidth = bi.biWidth * resizeFactor;
    int newHeight = bi.biHeight * resizeFactor;

    // deal with padding if necessary
    // old padding
    int padding =  (4 - (ogWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // new padding
    int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // already got data we needed from ogfile, can now set new height and width to biWidth and biHeight
    bi.biHeight = newHeight;
    bi.biWidth = newWidth;

    // update the header info for the new file
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * abs(newHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // printf("%d\n", bi.biWidth);
    // printf("%d\n", bi.biHeight);
    // printf("%d\n", bi.biSizeImage);
    // printf("%d\n", bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(ogHeight); i < biHeight; i++)
    {
        // set up an array to store each row of pixels

        // iterate over pixels in scanline
        for (int j = 0; j < ogWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // resize the width of image horizontally
            for (int k = 0; k < resizeFactor; k++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over old padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // add the new padding back in if needed
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}