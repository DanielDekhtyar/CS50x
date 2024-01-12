// Learning C with CS50x
// Filter
// https://cs50.harvard.edu/x/2024/psets/4/filter/less/


#include "helpers.h"
#include <math.h>

int black_and_whiteRGBT(RGBTRIPLE image);
int sepiaBlue(RGBTRIPLE image);
int sepiaGreen(RGBTRIPLE image);
int sepiaRed(RGBTRIPLE image);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int average = black_and_whiteRGBT(image[row][column]);
            image[row][column].rgbtBlue = average;
            image[row][column].rgbtGreen = average;
            image[row][column].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Call the functions and set the appropriate values for every pixel
            int sepBlue = sepiaBlue(image[row][column]);
            int sepGreen = sepiaGreen(image[row][column]);
            int sepRed = sepiaRed(image[row][column]);
            image[row][column].rgbtBlue = sepBlue;
            image[row][column].rgbtGreen = sepGreen;
            image[row][column].rgbtRed = sepRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int row = 0; row < height; row++)
    {
        // Initialize variables for swapping
        int start = 0;
        int end = width - 1;

        // Swap pixels from left to right within each row
        while (start < end)
        {
            // Swap the pixels
            RGBTRIPLE temp = image[row][start];
            image[row][start] = image[row][end];
            image[row][end] = temp;

            // Move to the next pair of pixels
            start++;
            end--;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // A temporary image to store the blurred image
    RGBTRIPLE temp[height][width];

    // Copy the original image to the temporary image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            temp[row][column].rgbtBlue = image[row][column].rgbtBlue;
            temp[row][column].rgbtGreen = image[row][column].rgbtGreen;
            temp[row][column].rgbtRed = image[row][column].rgbtRed;
        }
    }

    // Those variables store the RGB values of the current pixel and the average RGB values of the surrounding pixels
    int blue, red, green;

    // Count how many pixels are in the surrounding area, so later we can calculate the average RGB values by dividing by the counter
    int counter;

    // Loop over all pixels in the image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Initialize all variables to 0 for each new pixel
            counter = 0;
            blue = green = red = 0;

            // For each pixel we will check over down, up, left and right to see if it meets the condition
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Check if it is still inside the image to avoid memory leak or segmentation fault
                    if (row + h > height-1 || row + h < 0 || column + w > width-1 || column + w < 0)
                    {
                        continue;
                    }

                    // Add the RGB values of the surrounding pixels to the total RGB values of the current pixel
                    blue += image[row+h][column+w].rgbtBlue;
                    green += image[row+h][column+w].rgbtGreen;
                    red += image[row+h][column+w].rgbtRed;
                    counter++;
                }
            }

            // Set the average RGB values of the current pixel to the temporary image
            temp[row][column].rgbtBlue = round(blue / (float)counter);
            temp[row][column].rgbtGreen = round(green / (float)counter);
            temp[row][column].rgbtRed = round(red / (float)counter);
        }
    }

    // Copy the blurred image from temp to the original image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtBlue = temp[row][column].rgbtBlue;
            image[row][column].rgbtGreen = temp[row][column].rgbtGreen;
            image[row][column].rgbtRed = temp[row][column].rgbtRed;
        }
    }

    return;
}


// Return what the average color of the image is
int black_and_whiteRGBT(RGBTRIPLE image)
{
    float rgbtBW = (image.rgbtBlue + image.rgbtGreen + image.rgbtRed) / 3.0;
    return round(rgbtBW);
}

int sepiaBlue(RGBTRIPLE image)
{
    // Get the sepia blue value according to the formula
    int sepiaBlue = round(.272 * image.rgbtRed + .534 * image.rgbtGreen + .131 * image.rgbtBlue);
    
    // If the value is greater than 255, set it to 255
    if (sepiaBlue > 255)
    {
        sepiaBlue = 255;
    }

    // Return the result
    return sepiaBlue;
}

int sepiaGreen(RGBTRIPLE image)
{
    // Get the sepia green value according to the formula
    int sepiaGreen = round(.349 * image.rgbtRed + .686 * image.rgbtGreen + .168 * image.rgbtBlue);

    // If the value is greater than 255, set it to 255
    if (sepiaGreen > 255)
    {
        sepiaGreen = 255;
    }

    // Return the result
    return sepiaGreen;
}


int sepiaRed(RGBTRIPLE image)
{
    // Get the sepia red value according to the formula
    int sepiaRed = round(.393 * image.rgbtRed + .769 * image.rgbtGreen + .189 * image.rgbtBlue);

    // If the value is greater than 255, set it to 255
    if (sepiaRed > 255)
    {
        sepiaRed = 255;
    }

    // Return the result
    return sepiaRed;
}
