#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_header(uint8_t *buffer);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "rb");

    // Create a buffer for a block of data
    uint8_t buffer[512];

    int JPEG_count = 0;
    char filename[8];
    FILE *img = NULL; // Initialize img to NULL

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        if (is_header(buffer))
        {
            if (img != NULL)
            {
                // Close the current JPEG file
                fclose(img);
            }

            // Create a new JPEG file
            sprintf(filename, "%03i.jpg", JPEG_count);
            img = fopen(filename, "wb");
            fwrite(buffer, 1, 512, img);
            JPEG_count++;
        }
        else
        {
            if (img != NULL)
            {
                // Write to the current JPEG file
                fwrite(buffer, 1, 512, img);
            }
        }
    }

    // Close the last JPEG file
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the memory card file
    fclose(card);

    return 0;
}

bool is_header(uint8_t *buffer)
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
}
