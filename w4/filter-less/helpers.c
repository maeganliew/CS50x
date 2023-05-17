#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            int result = round((image[column][row].rgbtBlue + image[column][row].rgbtGreen + image[column][row].rgbtRed) / 3.0);
            image[column][row].rgbtBlue = image[column][row].rgbtGreen = image[column][row].rgbtRed = result;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            int red = round(.393 * image[column][row].rgbtRed + .769 * image[column][row].rgbtGreen + .189 * image[column][row].rgbtBlue);
            int green = round(.349 * image[column][row].rgbtRed + .686 * image[column][row].rgbtGreen + .168 * image[column][row].rgbtBlue);
            int blue = round(.272 * image[column][row].rgbtRed + .534 * image[column][row].rgbtGreen + .131 * image[column][row].rgbtBlue);
            image[column][row].rgbtRed = (red > 255) ? 255 : red;
            image[column][row].rgbtGreen = (green > 255) ? 255 : green;
            image[column][row].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }
    return ;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
        for (int column = 0; column < height; column++)
        {
                for (int row = 0; row < width / 2; row++)
                {
                    RGBTRIPLE temp[height][width];
                    temp[column][row] = image[column][row];
                    image[column][row] = image[column][width - row - 1];
                    image[column][width - row - 1] = temp[column][row];
                }
        }
        return ;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int column = 0; column < height; column++)
    {
        for (int row = 0; row < width; row++)
        {
            float red = 0.0;
            float green = 0.0;
            float blue = 0.0;
            float i = 0.0; //line 79 is dividing (float)rgb with i, i should be float

            for (int c = -1; c <= 1; c++)
            {
                for (int r = -1; r <= 1; r++)
                {
                    if (column + c < 0 || column + c > height - 1)
                        continue;   //rest of the loop gets ignored
                    if (row + r < 0 || row + r > width - 1)
                        continue;
                    red += image[column + c][row + r].rgbtRed;
                    blue += image[column + c][row + r].rgbtBlue;
                    green += image[column + c][row + r].rgbtGreen;
                    i++; //count number of grids that are involved
                }
            }
            temp[column][row].rgbtRed = round(red/i);
            temp[column][row].rgbtBlue = round(blue/i);
            temp[column][row].rgbtGreen = round(green/i);
        }
    }
    for (int column = 0; column < height; column++) //need another for loop because, if staight away store values to image[column][row], would change values of pixels. then further calculations would be based on new pixel.
    {
        for (int row = 0; row < width; row++)
        {
            image[column][row].rgbtRed = temp[column][row].rgbtRed;
            image[column][row].rgbtBlue = temp[column][row].rgbtBlue;
            image[column][row].rgbtGreen = temp[column][row].rgbtGreen;
        }
    }
    return;
}