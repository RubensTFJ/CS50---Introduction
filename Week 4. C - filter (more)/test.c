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
/*
    //Blur Corners.
    result[0][0].rgbtRed = (image[0][0].rgbtRed + image[0][1].rgbtRed + image [1][0].rgbtRed + image [1][1].rgbtRed)/4;
    result[0][0].rgbtBlue = (image[0][0].rgbtBlue + image[0][1].rgbtBlue + image [1][0].rgbtBlue + image [1][1].rgbtBlue)/4;
    result[0][0].rgbtGreen = (image[0][0].rgbtGreen + image[0][1].rgbtGreen + image [1][0].rgbtGreen + image [1][1].rgbtGreen)/4;

    result[0][width-1].rgbtRed = (image[0][width-1].rgbtRed + image[0][width-2].rgbtRed + image [1][width-1].rgbtRed + image [1][width -2].rgbtRed)/4;
    result[0][width-1].rgbtBlue = (image[0][width-1].rgbtBlue + image[0][width-2].rgbtBlue + image [1][width-1].rgbtBlue + image [1][width -2].rgbtBlue)/4;
    result[0][width-1].rgbtGreen = (image[0][width-1].rgbtGreen + image[0][width-2].rgbtGreen + image [1][width-1].rgbtGreen + image [1][width -2].rgbtGreen)/4;

    result[height-1][0].rgbtRed = (image[height-1][0].rgbtRed + image[height-1][1].rgbtRed + image [height-2][0].rgbtRed + image [height-2][1].rgbtRed)/4;
    result[height-1][0].rgbtBlue = (image[height-1][0].rgbtBlue + image[height-1][1].rgbtBlue + image [height-2][0].rgbtBlue + image [height-2][1].rgbtBlue)/4;
    result[height-1][0].rgbtGreen = (image[height-1][0].rgbtGreen + image[height-1][1].rgbtGreen + image [height-2][0].rgbtGreen + image [height-2][1].rgbtGreen)/4;

    result[height-1][width-1].rgbtRed = (image[height-1][width-1].rgbtRed + image[height-1][width-2].rgbtRed + image [height-2][width-1].rgbtRed + image [height-2][width-2].rgbtRed)/4;
    result[height-1][width-1].rgbtBlue = (image[height-1][width-1].rgbtBlue + image[height-1][width-2].rgbtBlue + image [height-2][width-1].rgbtBlue + image [height-2][width-2].rgbtBlue)/4;
    result[height-1][width-1].rgbtGreen = (image[height-1][width-1].rgbtGreen + image[height-1][width-2].rgbtGreen + image [height-2][width-1].rgbtGreen + image [height-2][width-2].rgbtGreen)/4;


    //Blur First and Last Lines (Minus the Corners).
    for(int i = 1; i < (width - 1); i++)
    {
        //First line.
        result[0][i].rgbtRed = (image[0][i-1].rgbtRed + image[0][i].rgbtRed + image[0][i+1].rgbtRed + image[1][i-1].rgbtRed + image[1][i].rgbtRed + image[1][i+1].rgbtRed)/6;
        result[0][i].rgbtBlue = (image[0][i-1].rgbtBlue + image[0][i].rgbtBlue + image[0][i+1].rgbtBlue + image[1][i-1].rgbtBlue + image[1][i].rgbtBlue + image[1][i+1].rgbtBlue)/6;
        result[0][i].rgbtGreen = (image[0][i-1].rgbtGreen + image[0][i].rgbtGreen + image[0][i+1].rgbtGreen + image[1][i-1].rgbtGreen + image[1][i].rgbtGreen + image[1][i+1].rgbtGreen)/6;

        //Last Line.
        result[height-1][i].rgbtRed = (image[height-1][i-1].rgbtRed + image[height-1][i].rgbtRed + image[height-1][i+1].rgbtRed + image[height-2][i-1].rgbtRed + image[height-2][i].rgbtRed + image[height-2][i+1].rgbtRed)/6;
        result[height-1][i].rgbtBlue = (image[height-1][i-1].rgbtBlue + image[height-1][i].rgbtBlue + image[height-1][i+1].rgbtBlue + image[height-2][i-1].rgbtBlue + image[height-2][i].rgbtBlue + image[height-2][i+1].rgbtBlue)/6;
        result[height-1][i].rgbtGreen = (image[height-1][i-1].rgbtGreen + image[height-1][i].rgbtGreen + image[height-1][i+1].rgbtGreen + image[height-2][i-1].rgbtGreen + image[height-2][i].rgbtGreen + image[height-2][i+1].rgbtGreen)/6;
    }

    //Blur First and Last Columns (Minus the Corners).
    for(int i = 1; i < (height - 1); i++)
    {
        //First line.
        result[i][0].rgbtRed = (image[i-1][0].rgbtRed + image[i][0].rgbtRed + image[i+1][0].rgbtRed + image[i-1][1].rgbtRed + image[i][1].rgbtRed + image[i+1][1].rgbtRed)/6;
        result[i][0].rgbtBlue = (image[i-1][0].rgbtBlue + image[i][0].rgbtBlue + image[i+1][0].rgbtBlue + image[i-1][1].rgbtBlue + image[i][1].rgbtBlue + image[i+1][1].rgbtBlue)/6;
        result[i][0].rgbtGreen = (image[i-1][0].rgbtGreen + image[i][0].rgbtGreen + image[i+1][0].rgbtGreen + image[i-1][1].rgbtGreen + image[i][1].rgbtGreen + image[i+1][1].rgbtGreen)/6;

        //Last Line.
        result[i][width - 1].rgbtRed = (image[i-1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i+1][width - 1].rgbtRed + image[i-1][width - 2].rgbtRed + image[i][width - 2].rgbtRed + image[i+1][width - 2].rgbtRed)/6;
        result[i][width - 1].rgbtBlue = (image[i-1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i+1][width - 1].rgbtBlue + image[i-1][width - 2].rgbtBlue + image[i][width - 2].rgbtBlue + image[i+1][width - 2].rgbtBlue)/6;
        result[i][width - 1].rgbtGreen = (image[i-1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i+1][width - 1].rgbtGreen + image[i-1][width - 2].rgbtGreen + image[i][width - 2].rgbtGreen + image[i+1][width - 2].rgbtGreen)/6;
    }
*/

    //Blur Middle Grid. (Minus the Borders).
    for(int i = 0; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
            result[i][j]  = getaverage(i, j, height, width, image);
        }
    }
    image = result;
    return;
}


RGBTRIPLE getaverage(int h, int w, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average;
    int times = 0;
    average.rgbtRed = 0;
    average.rgbtGreen = 0;
    average.rgbtBlue = 0;

    for( int i = (h-1); i < (h+2); i ++)
    {
        for(int j = (w-1); j < (w-2); j++)
        {
            if(i >= 0 && j >= 0)
            {
                average.rgbtRed = average.rgbtRed + image[i][j].rgbtRed;
                average.rgbtGreen = average.rgbtGreen + image[i][j].rgbtGreen;
                average.rgbtBlue = average.rgbtBlue + image[i][j].rgbtBlue;
                times = times + 1;
            }
        }
    }
    average.rgbtRed = average.rgbtRed/times;
    average.rgbtGreen = average.rgbtGreen/times;
    average.rgbtBlue = average.rgbtBlue/times;
    return average;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

/*
    //Blur Corners.
    result[0][0].rgbtRed = (image[0][0].rgbtRed + image[0][1].rgbtRed + image [1][0].rgbtRed + image [1][1].rgbtRed)/4;
    result[0][0].rgbtBlue = (image[0][0].rgbtBlue + image[0][1].rgbtBlue + image [1][0].rgbtBlue + image [1][1].rgbtBlue)/4;
    result[0][0].rgbtGreen = (image[0][0].rgbtGreen + image[0][1].rgbtGreen + image [1][0].rgbtGreen + image [1][1].rgbtGreen)/4;

    result[0][width-1].rgbtRed = (image[0][width-1].rgbtRed + image[0][width-2].rgbtRed + image [1][width-1].rgbtRed + image [1][width -2].rgbtRed)/4;
    result[0][width-1].rgbtBlue = (image[0][width-1].rgbtBlue + image[0][width-2].rgbtBlue + image [1][width-1].rgbtBlue + image [1][width -2].rgbtBlue)/4;
    result[0][width-1].rgbtGreen = (image[0][width-1].rgbtGreen + image[0][width-2].rgbtGreen + image [1][width-1].rgbtGreen + image [1][width -2].rgbtGreen)/4;

    result[height-1][0].rgbtRed = (image[height-1][0].rgbtRed + image[height-1][1].rgbtRed + image [height-2][0].rgbtRed + image [height-2][1].rgbtRed)/4;
    result[height-1][0].rgbtBlue = (image[height-1][0].rgbtBlue + image[height-1][1].rgbtBlue + image [height-2][0].rgbtBlue + image [height-2][1].rgbtBlue)/4;
    result[height-1][0].rgbtGreen = (image[height-1][0].rgbtGreen + image[height-1][1].rgbtGreen + image [height-2][0].rgbtGreen + image [height-2][1].rgbtGreen)/4;

    result[height-1][width-1].rgbtRed = (image[height-1][width-1].rgbtRed + image[height-1][width-2].rgbtRed + image [height-2][width-1].rgbtRed + image [height-2][width-2].rgbtRed)/4;
    result[height-1][width-1].rgbtBlue = (image[height-1][width-1].rgbtBlue + image[height-1][width-2].rgbtBlue + image [height-2][width-1].rgbtBlue + image [height-2][width-2].rgbtBlue)/4;
    result[height-1][width-1].rgbtGreen = (image[height-1][width-1].rgbtGreen + image[height-1][width-2].rgbtGreen + image [height-2][width-1].rgbtGreen + image [height-2][width-2].rgbtGreen)/4;


    //Blur First and Last Lines (Minus the Corners).
    for(int i = 1; i < (width - 1); i++)
    {
        //First line.
        result[0][i].rgbtRed = (image[0][i-1].rgbtRed + image[0][i].rgbtRed + image[0][i+1].rgbtRed + image[1][i-1].rgbtRed + image[1][i].rgbtRed + image[1][i+1].rgbtRed)/6;
        result[0][i].rgbtBlue = (image[0][i-1].rgbtBlue + image[0][i].rgbtBlue + image[0][i+1].rgbtBlue + image[1][i-1].rgbtBlue + image[1][i].rgbtBlue + image[1][i+1].rgbtBlue)/6;
        result[0][i].rgbtGreen = (image[0][i-1].rgbtGreen + image[0][i].rgbtGreen + image[0][i+1].rgbtGreen + image[1][i-1].rgbtGreen + image[1][i].rgbtGreen + image[1][i+1].rgbtGreen)/6;

        //Last Line.
        result[height-1][i].rgbtRed = (image[height-1][i-1].rgbtRed + image[height-1][i].rgbtRed + image[height-1][i+1].rgbtRed + image[height-2][i-1].rgbtRed + image[height-2][i].rgbtRed + image[height-2][i+1].rgbtRed)/6;
        result[height-1][i].rgbtBlue = (image[height-1][i-1].rgbtBlue + image[height-1][i].rgbtBlue + image[height-1][i+1].rgbtBlue + image[height-2][i-1].rgbtBlue + image[height-2][i].rgbtBlue + image[height-2][i+1].rgbtBlue)/6;
        result[height-1][i].rgbtGreen = (image[height-1][i-1].rgbtGreen + image[height-1][i].rgbtGreen + image[height-1][i+1].rgbtGreen + image[height-2][i-1].rgbtGreen + image[height-2][i].rgbtGreen + image[height-2][i+1].rgbtGreen)/6;
    }

    //Blur First and Last Columns (Minus the Corners).
    for(int i = 1; i < (height - 1); i++)
    {
        //First line.
        result[i][0].rgbtRed = (image[i-1][0].rgbtRed + image[i][0].rgbtRed + image[i+1][0].rgbtRed + image[i-1][1].rgbtRed + image[i][1].rgbtRed + image[i+1][1].rgbtRed)/6;
        result[i][0].rgbtBlue = (image[i-1][0].rgbtBlue + image[i][0].rgbtBlue + image[i+1][0].rgbtBlue + image[i-1][1].rgbtBlue + image[i][1].rgbtBlue + image[i+1][1].rgbtBlue)/6;
        result[i][0].rgbtGreen = (image[i-1][0].rgbtGreen + image[i][0].rgbtGreen + image[i+1][0].rgbtGreen + image[i-1][1].rgbtGreen + image[i][1].rgbtGreen + image[i+1][1].rgbtGreen)/6;

        //Last Line.
        result[i][width - 1].rgbtRed = (image[i-1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i+1][width - 1].rgbtRed + image[i-1][width - 2].rgbtRed + image[i][width - 2].rgbtRed + image[i+1][width - 2].rgbtRed)/6;
        result[i][width - 1].rgbtBlue = (image[i-1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i+1][width - 1].rgbtBlue + image[i-1][width - 2].rgbtBlue + image[i][width - 2].rgbtBlue + image[i+1][width - 2].rgbtBlue)/6;
        result[i][width - 1].rgbtGreen = (image[i-1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i+1][width - 1].rgbtGreen + image[i-1][width - 2].rgbtGreen + image[i][width - 2].rgbtGreen + image[i+1][width - 2].rgbtGreen)/6;
    }
*/
