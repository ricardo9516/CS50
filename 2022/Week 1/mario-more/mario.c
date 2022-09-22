#include <cs50.h>
#include <stdio.h>

void mario_pyramid(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    mario_pyramid(height);
}

void mario_pyramid(int height)
{
    int index = 2; //Used to check the limit of the nested loop
    for (int i = height; i > 0; i--) //Loop to go through the rows
    {
        for (int j = 0; j < i + index; j++)//Loop to go through the columns
        {
            if (i - 1 > j)
            {
                printf(" ");
            }
            else if (j < height)
            {
                printf("#");
            }
            else if (j == height)
            {
                printf("  ");
            }
            else
            {
                printf("#");
            }

        }
        printf("\n");
        index = index + 2;
    }
}