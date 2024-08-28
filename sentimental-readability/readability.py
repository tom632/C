# TODO
from cs50 import get_string


def main():
    # Get the string from the user
    text = get_string("Please enter the text: ")

    wordCount = 0
    letterCount = 0
    sentenceCount = 0

    # get the total number of words in the string
    wordCount = count_words(text)

    # get the total number of letters in the string
    letterCount = count_letters(text)

    # get the total number of sentences in the string
    sentenceCount = count_sentence(text)

    # do the calculation for the grade
    l = (letterCount / float(wordCount) * 100)
    s = (sentenceCount / float(wordCount) * 100)

    grade = round(0.0588 * l - 0.296 * s - 15.8)

    # out put to the user the correct grade
    if grade < 1:
        print("Before Grade 1 ")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade", grade)


# this function take in the text and returns the number of words in it


def count_words(text):
    words = 0
    words = len(text.split())
    return words

# this function takes in the text and return the number of letters in it


def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if (text[i].isalpha()):
            letters += 1
    return letters

# this function takes in the text and returns the number of sentences in it


def count_sentence(text):
    sentence = 0
    for i in range(len(text)):
        if text[i] == '?' or text[i] == '!' or text[i] == '.':
            sentence += 1
    return sentence


# call the main function
main()