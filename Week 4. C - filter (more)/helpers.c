#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float greyvalue;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            greyvalue = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            greyvalue = round(greyvalue);
            image[i][j].rgbtBlue = greyvalue;
            image[i][j].rgbtGreen = greyvalue;
            image[i][j].rgbtRed = greyvalue;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = width/2;
    RGBTRIPLE temp;

    // Copy pixel 'A' to variable, swap pixels 'A' and 'B', paste variable to pixel 'B'.
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < middle; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width -1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

RGBTRIPLE getaverage();
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE result[height][width];

    //Blur each pixel to a temp variable.
    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
            result[i][j] = getaverage(i, j, height, width, image);
        }
    }
    //Copy the changes made to the original image.
    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = result[i][j];
        }
    }

    return;
}


RGBTRIPLE getaverage(int h, int w, int height, int width, RGBTRIPLE image[height][width])
{
    //Variable to store and return.
    RGBTRIPLE average;
    float red = 0;
    float blue = 0;
    float green = 0;
    //Define the "pixel box", the loop limits.
    int initiali = (h - 1);
    int initialj = (w - 1);
    int imax = (h + 2);
    int jmax = (w + 2);

    if(initiali < 0)
    {
        initiali = 0;
    }

    if(initialj < 0)
    {
        initialj = 0;
    }

    if(imax > height)
    {
        imax = height;
    }

    if(jmax > width)
    {
        jmax = width;
    }

    float times = (imax - initiali)*(jmax - initialj);

    for(int i = initiali; i < imax; i ++)
    {
        for(int j = initialj; j < jmax; j++)
        {
            red = red + image[i][j].rgbtRed;
            green = green + image[i][j].rgbtGreen;
            blue = blue + image[i][j].rgbtBlue;
        }
    }

    red = 1.0*red/times;
    average.rgbtRed = round(red);
    green = 1.0*green/times;
    average.rgbtGreen = round(green);
    blue = 1.0*blue/times;
    average.rgbtBlue = round(blue);

    return average;
}

RGBTRIPLE function(int h, int w, int height, int width, RGBTRIPLE image[height+2][width+2]);
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE result[height+2][width+2];

    // Create Black Border. (First and last lines).
    for(int i = 0; i < (width+2); i++)
    {
        result[0][i].rgbtRed = 0;
        result[0][i].rgbtBlue = 0;
        result[0][i].rgbtGreen = 0;
        result[height+1][i].rgbtRed = 0;
        result[height+1][i].rgbtBlue = 0;
        result[height+1][i].rgbtGreen = 0;
    }

    // Create Black Border. (First and last Columns).
    for(int i = 0; i < (height+2); i++)
    {
        result[i][0].rgbtRed = 0;
        result[i][0].rgbtBlue = 0;
        result[i][0].rgbtGreen = 0;
        result[i][width+1].rgbtRed = 0;
        result[i][width+1].rgbtBlue = 0;
        result[i][width+1].rgbtGreen = 0;
    }

    // Copy image to the new variable's center.
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            result[i+1][j+1] = image[i][j];
        }
    }

    // Call Function to do Edges to each Pixel.
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = function((i+1), (j+1), height, width, result);
        }
    }
    return;
}

RGBTRIPLE function(int h, int w, int height, int width, RGBTRIPLE image[height+2][width+2])
{
    // Return Variable.
    RGBTRIPLE pixel;
    // Color Variables for Calculations;
    float red[] = {0, 0};
    float blue[] = {0, 0};
    float green[] = {0, 0};
    int hmatrix[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int vmatrix[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    // Variable 't' Tracks the matrixes's position on the loops.
    int t = 0;

    for(int i = (h-1); i < (h+2); i++)
    {
        for(int j = (w-1); j < (w+2); j++)
        {
            red[0] = red[0] + image[i][j].rgbtRed * hmatrix[t];
            blue[0] = blue[0] +  image[i][j].rgbtBlue * hmatrix[t];
            green[0] = green[0] + image[i][j].rgbtGreen * hmatrix[t];

            red[1] = red[1] + image[i][j].rgbtRed * vmatrix[t];
            blue[1] = blue[1] + image[i][j].rgbtBlue * vmatrix[t];
            green[1] = green[1] + image[i][j].rgbtGreen * vmatrix[t];

            t++;
        }
    }

    red[0] = sqrt((red[0]*red[0] + red[1]*red[1]));
    red[0] = round(red[0]);
    blue[0] = sqrt((blue[0]*blue[0] + blue[1]*blue[1]));
    blue[0] = round(blue[0]);
    green[0] = sqrt((green[0]*green[0] + green[1]*green[1]));
    green[0] = round(green[0]);

    if(red[0] > 255)
    {
        red[0] = 255;
    }
    if(blue[0] > 255)
    {
        blue[0] = 255;
    }
    if(green[0] > 255)
    {
        green[0] = 255;
    }

    pixel.rgbtRed = red[0];
    pixel.rgbtBlue = blue[0];
    pixel.rgbtGreen = green[0];

    return pixel;
}