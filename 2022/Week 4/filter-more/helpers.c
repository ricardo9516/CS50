#include "helpers.h"
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) //WORKING
{
    int avg = 0; //Variable to calculate avg
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Gets the average of RGB and inserts it in each value.
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) //WORKING
{
    int tmpR = 0;
    int tmpB = 0;
    int tmpG = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmpR = image[i][j].rgbtRed;
            tmpB = image[i][j].rgbtBlue;
            tmpG = image[i][j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtRed = tmpR;
            image[i][width - 1 - j].rgbtGreen = tmpG;
            image[i][width - 1 - j].rgbtBlue = tmpB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) //WORKING
{
    int avgR = 0; //Saves the avg amount of Red
    int avgG = 0; //Saves the avg amount of Green
    int avgB = 0; //Saves the avg amount of Blue
    RGBTRIPLE imagecopy[height][width]; //copy of image to save tmp values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //Top left corner
            if (i == 0 && j == 0)
            {
                avgR = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed
                              + image[i + 1][j + 1].rgbtRed) / (float) 4);
                avgG = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen
                              + image[i + 1][j + 1].rgbtGreen) / (float) 4);
                avgB = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue
                              + image[i + 1][j + 1].rgbtBlue) / (float) 4);
            }
            //Top
            else if (i == 0 && j > 0 && j < width - 1)
            {
                avgR = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed
                              + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / (float) 6);
                avgG = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen
                              + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) / (float) 6);
                avgB = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue
                              + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / (float) 6);
            }
            //Top right corner
            else if (i == 0 && j == width - 1)
            {
                avgR = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed
                              + image[i + 1][j - 1].rgbtRed) / (float) 4);
                avgG = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen
                              + image[i + 1][j - 1].rgbtGreen) / (float) 4);
                avgB = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue
                              + image[i + 1][j - 1].rgbtBlue) / (float) 4);
            }
            //Left
            else if (i > 0 && i < height - 1 && j == 0)
            {
                avgR = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed
                              + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) / (float) 6);
                avgG = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen
                              + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / (float) 6);
                avgB = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue
                              + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / (float) 6);
            }
            //Right
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                avgR = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed
                              + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed) / (float) 6);
                avgG = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen
                              + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) / (float) 6);
                avgB = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue
                              + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) / (float) 6);
            }
            //Bottom left corner
            else if (i == height - 1 && j == 0)
            {
                avgR = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed
                              + image[i - 1][j + 1].rgbtRed) / (float) 4);
                avgG = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen
                              + image[i - 1][j + 1].rgbtGreen) / (float) 4);
                avgB = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue
                              + image[i - 1][j + 1].rgbtBlue) / (float) 4);
            }
            //Bottom
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                avgR = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed
                              + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / (float) 6);
                avgG = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                              + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / (float) 6);
                avgB = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                              + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / (float) 6);
            }
            //Bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                avgR = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed
                              + image[i - 1][j].rgbtRed) / (float) 4);
                avgG = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                              + image[i - 1][j].rgbtGreen) / (float) 4);
                avgB = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                              + image[i - 1][j].rgbtBlue) / (float) 4);
            }
            //Middle
            else
            {
                avgR = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed
                              + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed
                              + image[i - 1][j - 1].rgbtRed) / (float) 9);
                avgG = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen
                              + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen
                              + image[i - 1][j - 1].rgbtGreen) / (float) 9);
                avgB = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue
                              + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue
                              + image[i - 1][j - 1].rgbtBlue) / (float) 9);
            }
            //Set the values on the image
            imagecopy[i][j].rgbtRed = avgR;
            imagecopy[i][j].rgbtGreen = avgG;
            imagecopy[i][j].rgbtBlue = avgB;
        }
    }
    //Set image to values saved on imagecopy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed ;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int GxR, GyR, GxG, GyG, GxB, GyB; //Temporal values to save the Gx and Gy
    int totalR = 0; //Saves total red from algorithm with gx and gy
    int totalG = 0; //Saves total green from algorithm with gx and gy
    int totalB = 0; //Saves total blue from algorithm with gx and gy
    RGBTRIPLE imagecopy[height][width];

    /* GX Convulotional matrix
    -1 0 1
    -2 0 2
    -1 0 1
    */
    /* Gy Convulotional matrix
    -1 -2 -1
     0  0  0
     1  2  1
    */

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //Top left corner
            if (i == 0 && j == 0)
            {
                GxR = image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
                GxG = image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                GxB = image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;
                GyR = image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
                GyG = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                GyB = image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;

            }
            //Top
            else if (i == 0 && j > 0 && j < width - 1)
            {

                GxR = image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed * -1 + image[i][j - 1].rgbtRed * -2;
                GxG = image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen * -1
                      + image[i][j - 1].rgbtGreen * -2;
                GxB = image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue * -1
                      + image[i][j - 1].rgbtBlue * -2;
                GyR = image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed;
                GyG = image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen;
                GyB = image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue;
            }
            //Top right corner
            else if (i == 0 && j == width - 1)
            {
                GxR = image[i][j - 1].rgbtRed * -2 + image[i + 1][j - 1].rgbtRed * -1;
                GxG = image[i][j - 1].rgbtGreen * -2 + image[i + 1][j - 1].rgbtGreen * -1;
                GxB = image[i][j - 1].rgbtBlue * -2 + image[i + 1][j - 1].rgbtBlue * -1;
                GyR = image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed;
                GyG = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen;
                GyB = image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue;
            }
            //Left
            else if (i > 0 && i < height - 1 && j == 0)
            {
                GxR = image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed;
                GxG = image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen;
                GxB = image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue;
                GyR = image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1 + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed * 2;
                GyG = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1 + image[i + 1][j + 1].rgbtGreen
                      + image[i + 1][j].rgbtGreen * 2;
                GyB = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1 + image[i + 1][j + 1].rgbtBlue
                      + image[i + 1][j].rgbtBlue * 2;
            }
            //Right
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                GxR = image[i + 1][j - 1].rgbtRed * -1 + image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1;
                GxG = image[i + 1][j - 1].rgbtGreen * -1 + image[i][j - 1].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1;
                GxB = image[i + 1][j - 1].rgbtBlue * -1 + image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1;
                GyR = image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * -2;
                GyG = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen * -1
                      + image[i - 1][j].rgbtGreen * -2;
                GyB = image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue * -1
                      + image[i - 1][j].rgbtBlue * -2;
            }
            //Bottom left corner
            else if (i == height - 1 && j == 0)
            {
                GxR = image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed;
                GxG = image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen;
                GxB = image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue;
                GyR = image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1;
                GyG = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1;
                GyB = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1;
            }
            //Bottom
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                GxR = image[i][j + 1].rgbtRed * 2 + image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1
                      + image[i - 1][j + 1].rgbtRed;
                GxG = image[i][j + 1].rgbtGreen * 2 + image[i][j - 1].rgbtGreen * -2
                      + image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j + 1].rgbtGreen;
                GxB = image[i][j + 1].rgbtBlue * 2 + image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1
                      + image[i - 1][j + 1].rgbtBlue;
                GyR = image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1;
                GyG = image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1;
                GyB = image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1;
            }
            //Bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                GxR = image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1;
                GxG = image[i][j - 1].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1;
                GxB = image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1;
                GyR = image[i - 1][j - 1].rgbtRed * -1 + image[i - 1][j].rgbtRed * -2;
                GyG = image[i - 1][j - 1].rgbtGreen * -1 + image[i - 1][j].rgbtGreen * -2;
                GyB = image[i - 1][j - 1].rgbtBlue * -1 + image[i - 1][j].rgbtBlue * -2;
            }
            //Middle
            else
            {
                GxR = image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed * -1
                      + image[i][j - 1].rgbtRed * -2 + image[i - 1][j - 1].rgbtRed * -1;
                GxG = image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen
                      + image[i + 1][j - 1].rgbtGreen * -1 + image[i][j - 1].rgbtGreen * -2 + image[i - 1][j - 1].rgbtGreen * -1;
                GxB = image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue
                      + image[i + 1][j - 1].rgbtBlue * -1 + image[i][j - 1].rgbtBlue * -2 + image[i - 1][j - 1].rgbtBlue * -1;
                GyR = image[i - 1][j].rgbtRed * -2 + image[i - 1][j + 1].rgbtRed * -1 + image[i + 1][j + 1].rgbtRed
                      + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed * -1;
                GyG = image[i - 1][j].rgbtGreen * -2 + image[i - 1][j + 1].rgbtGreen * -1 + image[i + 1][j + 1].rgbtGreen
                      + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen * -1;
                GyB = image[i - 1][j].rgbtBlue * -2 + image[i - 1][j + 1].rgbtBlue * -1 + image[i + 1][j + 1].rgbtBlue
                      + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue * -1;
            }
            totalR = round(sqrt(GxR * GxR + GyR * GyR));
            totalG = round(sqrt(GxG * GxG + GyG * GyG));
            totalB = round(sqrt(GxB * GxB + GyB * GyB));
            if (totalR > 255)
            {
                imagecopy[i][j].rgbtRed = 255;
            }
            else
            {
                imagecopy[i][j].rgbtRed = totalR;
            }
            if (totalG > 255)
            {
                imagecopy[i][j].rgbtGreen = 255;
            }
            else
            {
                imagecopy[i][j].rgbtGreen = totalG;
            }
            if (totalB > 255)
            {
                imagecopy[i][j].rgbtBlue = 255;
            }
            else
            {
                imagecopy[i][j].rgbtBlue = totalB;
            }
        }
    }

    //Set image to values saved on imagecopy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed ;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
        }
    }
    return;
}

