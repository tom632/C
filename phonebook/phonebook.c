#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];
    people[0].name = "Tom";
    people[0].number = "+1-618-458-658";

    people[1].name = "david";
    people[1].number = "+1-648-485-695";


    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "Tom") == 0)
        {
            printf("Phone number: %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found: \n");
}