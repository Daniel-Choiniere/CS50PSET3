#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// open the memory card file
// repeat until end of the card
// read 512 bytes at a time
// find the beginning of JPEG
//      yes -->
//          open a new JPEG
//  write 512 bytes until the new JPEG is found
//  detect the end of the file
//       no -->
//          already found a JPEG
//      yes -->
//      no -->
//  close any remaing files


// create a filename for the new JPEG file
// sprintf(fiename, "%00.jpg", 2);

// // open the new JPEG file so we can work with it
// ex) FILE *img = fopen(filename, "w");

// // now that the new file is open we need to write each JPEG 512 bytes at a time
// fwrite(data, size, number, outptr);
// ex) fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr) *outptr is the file we just created

int main(int argc, char *argv[])
{
    // make sure the user only entered two arguments (the filename + the file to recover)
    if (argc != 2)
    {
        // printf("%i\n", argc);
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filename
    // the infile is the second argument
    char *infile = argv[1];

    // open input file
    FILE *fileToRead = fopen(infile, "r");
    if (fileToRead == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // create an empty 512 byte array to be able to look at the first few bytes of each chunk
    unsigned char buffer[512];

    // make a fileCounter to increase the file number each time a file is written
    int fileCounter = 0;

    // name of the new JPEG is stored in this array
    char recoveredPicName[8];

    // make an empty File to be able to fill when iterating through
    FILE *recoveredImg;

    // reads data from the given stream (i.e. fileToRead) into the array pointed to, (i.e. buffer)
    while (fread(buffer, sizeof(buffer), 1, fileToRead) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if we already have a previous img file open, close it
            if (fileCounter > 0)
            {
                fclose(recoveredImg);

                // names the new img file using sprintf
                // sends formatted output to a string pointed to, by str. (i.e. recoveredPicName)
                sprintf(recoveredPicName, "%03d.jpg", fileCounter);

                // increase the counter by one for the next file name/number
                fileCounter ++;

                // open the newfile to write to
                recoveredImg = fopen(recoveredPicName, "w");

                // write to the newfile
                // writes data from the array pointed to, (i.e. buffer) to the given streamn (i.e. recoveredImg).
                fwrite(buffer, sizeof(buffer), 1, recoveredImg);
            }
            if (fileCounter == 0)
            {
                sprintf(recoveredPicName, "%03d.jpg", fileCounter);

                fileCounter ++;

                recoveredImg = fopen(recoveredPicName, "w");

                fwrite(buffer, sizeof(buffer), 1, recoveredImg);
            }
        }
        else if (fileCounter > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, recoveredImg);
        }
    }

    // close out files, and end program succesfully
    fclose(recoveredImg);
    fclose(fileToRead);

    return 0;
}
