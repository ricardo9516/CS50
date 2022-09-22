#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    BYTE buffer[512];
    int jpegCounter = 0;
    FILE *JPEG = NULL;
    char filename[8];

    //Cycle that will stop when there is no 512 memory chunks on the input file
    while (fread(&buffer, 512, 1, input) == 1)
    {
        //Verify if the 512 bytes chunk start with these hexadecimal numbers, if that is so then it is a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If it has find one then it will close the previous one
            if (!(jpegCounter == 0))
            {
                fclose(JPEG);
            }
            //Creates a file and opens it
            sprintf(filename, "%03i.jpg", jpegCounter);
            JPEG = fopen(filename, "w");
            jpegCounter++;
        }
        //It will keep writting on the new file if a jpeg has been found
        if (!(jpegCounter == 0))
        {
            fwrite(&buffer, 512, 1, JPEG);
        }
    }
    fclose(input);
    fclose(JPEG);
    return 0;
}
