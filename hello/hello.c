#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Ask the user to input thier name
    string name = get_string("Please enter your name? ");

    //out to the screen the data plus the users input
    printf("hello, %s\n", name);
}