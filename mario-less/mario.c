#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //setup the variables need for the program
    int blocks;
    do
    {
        //ask the user to input the amount of blocks
        blocks = get_int("Please enter the size of the blocks ");
    }
    while (blocks < 1 || blocks > 8);
    {
        for (int i = 1; i <= blocks; i++)
        {
            for (int j = 0; j < blocks - i; j++)
            {
                //output a blank space at the start of each row
                printf(" ");
            }
            for (int j = blocks - i; j < blocks; j++)
            {
                //output the block rows
                printf("#");
            }
            //move to the next row
            printf("\n");
        }
    }
}