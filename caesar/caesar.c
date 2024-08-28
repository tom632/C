#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check if the command line arguments = 2
    if (argc == 2)
    {
        //set the key to the second argument
        int key = atoi(argv[1]);
        bool valid_key = false;

        //loop around to check the key is valid
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
                valid_key = true;
            }
            else
            {
                printf("Usage ./caesar\n");
                return 1;
            }
        }

        //if the key is valid continue
        if (valid_key == true)
        {
            //get the users input
            string input = get_string("Please enter the text\n");

            for (int x = 0; x < strlen(input); x++)
            {
                //if the user input is uppercase change that
                if (isupper(input[x]))
                {
                    input[x] = ((input[x] - 65 + key) % 26) + 65;
                }
                //if the user input is lower case change that
                else if (islower(input[x]))
                {
                    input[x] = ((input[x] - 97 + key) % 26) + 97;
                }
            }
            //output the encoded text
            printf("ciphertext: %s\n", input);
        }
    }
    //output warning if the commandline arguments are incorrect
    else
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
}