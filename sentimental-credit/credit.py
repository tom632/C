# TODO
from cs50 import get_string


def main():
    # get the card number from the user
    cardNum = get_string("Number: ")

    # check the length of the card
    cardLen = len(str(cardNum))

    evenSum = 0
    oddSum = 0
    checkSum = 0

    # if the card number has the correct amount of numbers
    if cardLen != 13 and cardLen != 15 and cardLen != 16:
        print("INVALID")
        exit()

    for i in range(-2, (-cardLen-1), -2):

        tempMul = int(cardNum[i]) * 2

        if tempMul >= 10:
            evenSum = evenSum + tempMul - 9
        else:
            evenSum = evenSum + tempMul

    for i in range(-1, (-cardLen-1), -2):
        tempOdd = int(cardNum[i])
        oddSum = oddSum + tempOdd

    # total up so this can be checked for which card the number is
    checkSum = evenSum + oddSum

    if checkSum % 2 == 0:
        # Check for american express
        if int(cardNum[0]) == 3 and int(cardNum[1]) == 4 or int(cardNum[1]) == 7:
            print("AMEX")

        # check for mastercard
        elif int(cardNum[0]) == 5 and int(cardNum[1]) == 1 or int(cardNum[1]) == 2 or int(cardNum[1]) == 3 or int(cardNum[1]) == 4 or int(cardNum[1]) == 5:
            print("MASTERCARD")

        # check for visa
        elif int(cardNum[0]) == 4:
            print("VISA")

        # if the number matches none of the above then it is invalid
        else:
            print("INVALID")


# Call the main function
main()