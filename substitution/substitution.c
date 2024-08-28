#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        //check that there is only 26 letter in the string
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                //check the sting has no numbers
                if (!isalpha(argv[1][i]))
                {
                    printf("Non Alpha\n");
                    return 1;
                }
                for (int j = 0; j < strlen(argv[1]) - 1; j++)
                {
                    //check for duplicates in the string
                    if ((tolower(argv[1][i])) == (tolower(argv[1][i + 1])))
                    {
                        printf("duplicates:\n");
                        return 1;
                    }
                }
            }
        }

        //ask the user for the text
        string input = get_string("Please enter the text: \n");
        for (int x = 0; x < strlen(input); x++)
        {
            //if it is lower change it to the lower case
            if (islower(input[x]))
            {
                input[x] = tolower(argv[1][input[x] - 97]);
            }
            //if it is upper case change it to that
            else if (isupper(input[x]))
            {
                input[x] = toupper(argv[1][input[x] - 65]);
            }
        }
        //print out the encoded text
        printf("ciphertext: %s\n", input);
        return 0;
    }
    else
    {
        //error message if not all params are correct
        printf("Usage ./substitution key\n");
        return 1;
    }
}