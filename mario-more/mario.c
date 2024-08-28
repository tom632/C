#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int blocks;
    do
    {
        //Get the size from the user
        blocks = get_int("Please enter the size of the blocks ");
    }
    while (blocks < 1 || blocks > 8);
    {
        for (int i = 1; i <= blocks; i++)
        {
            //Create the left hand prymid
            for (int j = 0; j < blocks - i; j++)
            {
                printf(" ");
            }
            for (int j = blocks - i; j < blocks; j++)
            {
                printf("*");
            }

            //Add the gap in the middle
            for (int j = 0; j < 2; j++)
            {
                printf(" ");
            }

            //Create the right hand prymid
            for (int j = blocks - i; j < blocks; j++)
            {
                printf("*");
            }
            //move to the next row
            printf("\n");
        }
    }
}