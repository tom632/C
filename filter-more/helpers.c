#include "helpers.h"
#include <math.h>

void swap(RGBTRIPLE *a, RGBTRIPLE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum;
    float average;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //total the values
            sum = image[x][y].rgbtRed + image[x][y].rgbtBlue +
                  image[x][y].rgbtGreen;

            //calculate the average of the values
            average = sum / 3.0;

            //set the image values after rounding them
            image[x][y].rgbtRed = round(average);
            image[x][y].rgbtBlue = round(average);
            image[x][y].rgbtGreen = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width / 2; y++)
        {
            //call the swao function to swap around the numbers
            swap(&image[x][y], &image[x][width - 1 - y]);
        }
    }
    return;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    //this function will copy the values from one location to another
    RGBTRIPLE temp1 = *a;
    *a = *b;
    *b = temp1;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float counter, blue, red, green;

    //make a copy of the image
    RGBTRIPLE image2[height][width];

    //loop around and set the copy to the same as the original
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image2[x][y] = image[x][y];
        }
    }

    //loop around setting image2 with the new values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = 0;
            red = 0;
            green = 0;
            counter = 0;

            //loop around setting the new values to image 2
            for (int k = - 1; k < 2; k++)
            {
                for (int l = - 1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    blue += image2[i + k][j + l].rgbtBlue;
                    green += image2[i + k][j + l].rgbtGreen;
                    red += image2[i + k][j + l].rgbtRed;
                    counter++;
                }
            }
            //set image 1 to the values stored in image2
            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtBlue = round(blue / counter);
            image[i][j].rgbtGreen = round(green / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Ask for some temparory memories for store blur pixels
    RGBTRIPLE temp[height][width];

    // Consider every condition you may encounter with pixels
    int GxR, GyR, GxG, GyG, GxB, GyB;

    // Initialize Gx and Gy metrix
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxR = GyR = GxG = GyG = GxB = GyB = 0;

            // Loop over 3x3 pixels
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Check if this pixel is outside the image
                    if (i + h < 0 || i + h > height - 1)
                    {
                        continue;
                    }

                    if (j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }

                    // sum each channel value
                    // X
                    GxR += image[i + h][j + w].rgbtRed * Gx[h + 1][w + 1];
                    GxG += image[i + h][j + w].rgbtGreen * Gx[h + 1][w + 1];
                    GxB += image[i + h][j + w].rgbtBlue * Gx[h + 1][w + 1];

                    // Y
                    GyR += image[i + h][j + w].rgbtRed * Gy[h + 1][w + 1];
                    GyG += image[i + h][j + w].rgbtGreen * Gy[h + 1][w + 1];
                    GyB += image[i + h][j + w].rgbtBlue * Gy[h + 1][w + 1];
                }
            }

            // Calculate every Gx and Gy value and store in temp
            temp[i][j].rgbtRed   = fmin(round(sqrt(GxR * GxR + GyR * GyR)), 255);
            temp[i][j].rgbtGreen = fmin(round(sqrt(GxG * GxG + GyG * GyG)), 255);
            temp[i][j].rgbtBlue  = fmin(round(sqrt(GxB * GxB + GyB * GyB)), 255);

            // Capped color value at 255
            if (temp[i][j].rgbtRed > 255)
            {
                temp[i][j].rgbtRed = 255;
            }

            if (temp[i][j].rgbtGreen > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }

            if (temp[i][j].rgbtBlue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
        }
    }

    // Ready to iterate whole image from temp to image[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
