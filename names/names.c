#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    string names[] = {"bill", "Tom", "fred", "ron"};

    for (int i = 0; i < 3; i++)
    {
        if(strcmp(names[i], "Tom") == 0)
        {
            printf("Found name: %s\n", names[i]);
            return 0;
        }
    }
    printf("Not found:\n");
    return 1;
}