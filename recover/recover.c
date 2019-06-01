#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// open the memory card file
    // find the beginning of JPEG
    // open a new JPEG
        // write 512 bytes until the new JPEG is found
        // detect the end of the file

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


    // open the new JPEG file
    sprintf(fiename, "%00.jpg", 2);
    // write the new JPEG FILE
    fwrite(data, size, number, outptr);
}
