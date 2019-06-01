#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// open the memory card file
// repeat until end of the card
    // read 512 bytes at a time
    // find the beginning of JPEG
        // yes -->
            // open a new JPEG
            // write 512 bytes until the new JPEG is found
            // detect the end of the file
        // no -->
    // already found a JPEG
        // yes -->
        // no -->
// close any remaing files

int main(int argc, char *argv[])
{
     if (argc != 2)
    {
        // printf("%i\n", argc);
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // change the input to a number so we can work with it
    int resizeFactor = atoi(argv[1]);

    // remember filenames
    // infile is the second argument
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    } else
    {
        fprintf(stderr, "Opened: %s\n", infile);
        fread(&infile, 1, 512, inptr);
    }



    // // create a filename for the new JPEG file
    // sprintf(fiename, "%00.jpg", 2);

    // // open the new JPEG file so we can work with it
    // ex) FILE *img = fopen(filename, "w");

    // // now that the new file is open we need to write each JPEG 512 bytes at a time
    // fwrite(data, size, number, outptr);
    // ex) fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr) *outptr is the file we just created



}
