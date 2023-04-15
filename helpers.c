#include "helpers.h"
#include "math.h"
#include <stdio.h>
//
//
//
//
//
//
//
//
//
//
//
//
//
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE cur = image[i][j];
            float average = (cur.rgbtBlue + cur.rgbtGreen + cur.rgbtRed) / 3.0;
            image[i][j].rgbtBlue = roundf(average);
            image[i][j].rgbtGreen =  roundf(average);
            image[i][j].rgbtRed = roundf(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int new_b, new_g, new_r;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE cur = image[i][j];
            new_r = round(0.393 * cur.rgbtRed + 0.769 * cur.rgbtGreen + 0.189 * cur.rgbtBlue);
            new_g = round(0.349 * cur.rgbtRed + 0.686 * cur.rgbtGreen + 0.168 * cur.rgbtBlue);
            new_b = round(0.272 * cur.rgbtRed + 0.534 * cur.rgbtGreen + 0.131 * cur.rgbtBlue);
            if (new_r > 255)
            {
                new_r = 255;
            }
            if (new_g > 255)
            {
                new_g = 255;
            }
            if (new_b > 255)
            {
                new_b = 255;
            }
            image[i][j].rgbtBlue = new_b;
            image[i][j].rgbtGreen = new_g;
            image[i][j].rgbtRed = new_r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE left = image[i][j];
            RGBTRIPLE right = image[i][width - 1 - j];
            image[i][j] = right;
            image[i][width - 1 - j] = left;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("(%i, %i)\n", i, j);
            int start_row = i - 1;
            int end_row = i + 1;
            int start_col = j - 1;
            int end_col = j + 1;
            if (i - 1 < 0)
            {
                start_row = 0;
            }
            if (j - 1 < 0)
            {
                start_col = 0;
            }
            if (i + 1 >= height)
            {
                end_row = height - 1;
            }
            if (j + 1 >= width)
            {
                end_col = width - 1;
            }
            int average_r = 0.0, average_b = 0.0, average_g = 0.0;
            int c = 0;
            for (int sr = start_row; sr <= end_row; sr++)
            {
                for (int sc = start_col; sc <= end_col; sc++)
                {
                    average_r += copy[sr][sc].rgbtRed;
                    average_g += copy[sr][sc].rgbtGreen;
                    average_b += copy[sr][sc].rgbtBlue;
                    c++;
                }
            }
            image[i][j].rgbtRed = round(average_r / (float)c);
            image[i][j].rgbtGreen = round(average_g / (float)c);
            image[i][j].rgbtBlue = round(average_b / (float)c);
        }
    }
}
