#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //variables to be used
    int words = 0, letters = 0, sentence = 0, grade = 0;
    float s = 0, l = 0;

    //get the users input
    string name = get_string("Please enter the text:\n");

    //run the functions to calculate the number of letters words and sentences
    letters = count_letters(name);
    words = count_words(name);
    sentence = count_sentences(name);

    //do the calculation for the grade
    l = (letters / (float)words) * 100;
    s = (sentence / (float)words) * 100;

    grade = round(0.0588 * l - 0.296 * s - 15.8);

    //send the out put to the screen
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

//function for calculating the number of letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    //return the number of letterss
    return letters;
}

//function for calculating the number of words
int count_words(string text)
{
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    //return the number of words
    return words;
}

//function for calculating the number of sentences
int count_sentences(string text)
{
    int sentence = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
    }

    //return the number of sentences
    return sentence;
}