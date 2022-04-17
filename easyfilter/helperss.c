#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float average = round((float)(imageimage[i][j][j].rgbtBlue + imageimage[i][j][j].rgbtGreen + imageimage[i][j][j].rgbtRed) / 3);
            imageimage[i][j][j].rgbtBlue = average;
            imageimage[i][j][j].rgbtRed = average;
            imageimage[i][j][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int Ored = imageimage[i][j][j].rgbtRed;
            int Ogreen = imageimage[i][j][j].rgbtGreen;
            int Oblue = imageimage[i][j][j].rgbtBlue;
            float sepiaRed = round(0.393 * Ored + 0.769 * Ogreen + 0.189 * Oblue);
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            float sepiaGreen = round(0.349 * Ored + 0.686 * Ogreen + 0.168 * Oblue);
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            float sepiaBlue = round(0.272 * Ored + 0.534 * Ogreen + 0.131 * Oblue);
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            imageimage[i][j][j].rgbtRed = sepiaRed;
            imageimage[i][j][j].rgbtBlue = sepiaBlue;
            imageimage[i][j][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++)
        {
            int tempred = imageimage[i][j][j].rgbtRed;
            int tempblue = imageimage[i][j][j].rgbtBlue;
            int tempgreen = imageimage[i][j][j].rgbtGreen;

            imageimage[i][j][j].rgbtRed = imageimage[i][j][width - j - 1].rgbtRed;
            imageimage[i][j][j].rgbtGreen = imageimage[i][j][width - j - 1].rgbtGreen;
            imageimage[i][j][j].rgbtBlue = imageimage[i][j][width - j - 1].rgbtBlue;

            imageimage[i][j][width - j - 1].rgbtRed = tempred;
            imageimage[i][j][width - j - 1].rgbtBlue = tempblue;
            imageimage[i][j][width - j - 1].rgbtGreen = tempgreen;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpimage[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            float counter = 0.00;
            for(int x = -1; x < 2; x++)
            {
                int currentx = i + x;
                for(int y = -1; y < 2; y++)
                {
                    int currenty = j + y;
                    if(currentx > -1 && currentx <= (height - 1) && currenty > -1 && currenty <= (width - 1))
                    {
                    totalRed += image[currentx][currenty].rgbtRed;
                    totalBlue += image[currentx][currenty].rgbtBlue;
                    totalGreen += image[currentx][currenty].rgbtGreen;
                    counter++;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            tmpimageimage[i][j][j].rgbtRed = round(totalRed / counter);
            tmpimageimage[i][j][j].rgbtBlue = round(totalBlue / counter);
            tmpimageimage[i][j][j].rgbtGreen = round(totalGreen / counter);
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            imageimage[i][j][j].rgbtRed = tmpimageimage[i][j][j].rgbtRed;
            imageimage[i][j][j].rgbtGreen = tmpimageimage[i][j][j].rgbtGreen;
            imageimage[i][j][j].rgbtBlue = tmpimageimage[i][j][j].rgbtBlue;
        }
    }
    return;
}
