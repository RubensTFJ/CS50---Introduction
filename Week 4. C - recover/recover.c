#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int checkforjpeg();

int main(int argc, char *argv[])
{

    if(argc != 2)
    {
        printf("Usage: ./recover IMAGE.\n");
        return 1;
    }

    FILE *recover = fopen(argv[1], "r");
    if(recover == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    int jpegcounter = -1;
    FILE *file;
    bool write = false;
    char filename[8];

    while((fread(&buffer, sizeof(int8_t), 512, recover)) == 512)
    {
        if(checkforjpeg(buffer))
        {
            if(write == true)
            {
                fclose(file);
            }
            jpegcounter++;
            sprintf(filename, "%03i.jpg", jpegcounter);
            file = fopen(filename, "w");
            fwrite(&buffer, sizeof(int8_t), 512, file);
            write = true;
        }
        else if(write == true)
        {
            fwrite(&buffer, sizeof(int8_t), 512, file);
        }
    }

    return 0;

}

int checkforjpeg(uint8_t buffer[512])
{
    if(buffer[0] == 0xff)
    {
        if(buffer[1] == 0xd8)
        {
            if(buffer[2] == 0xff)
            {
                if(buffer[3] >= 0xe0 && buffer[3] <= 0xef)
                {
                    return 1;
                }
            }
        }
    }
return 0;

}