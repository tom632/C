#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red, blue, green;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //do the calculation for each color
            red = round(0.393 * image[x][y].rgbtRed + 0.769 * image[x][y].rgbtGreen + 0.189 * image[x][y].rgbtBlue);
            green = round(0.349 * image[x][y].rgbtRed + 0.686 * image[x][y].rgbtGreen + 0.168 * image[x][y].rgbtBlue);
            blue = round(0.272 * image[x][y].rgbtRed + 0.534 * image[x][y].rgbtGreen + 0.131 * image[x][y].rgbtBlue);

            //set each color to the value
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            //set the image value
            image[x][y].rgbtRed = red;
            image[x][y].rgbtBlue = blue;
            image[x][y].rgbtGreen = green;
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
