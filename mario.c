#include <stdio.h>
#include <cs50.h>
// Program that will ask for height and afterwards will show hashes according to that number as in Mario

int main(void)
{
    //Ask for the height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    //pyramid, two cycles to go up down and left right
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1 ; j <= height; j++)
        {
            //Checks level of pyramid to order right to left
            if (j > height - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

