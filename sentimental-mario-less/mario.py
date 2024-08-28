# TODO
# import the get_int function from cs50
from cs50 import get_int

while True:
    # ask the user for the number of blocks
    height = get_int("Number of blocks? ")
    # check the numbers are between 1 and 9
    if height > 0 and height < 9:
        break
# loop around and print the blocks based on the users input
for row in range(height):
    for space in range(height - row - 1, 0, -1):
        print(" ", end="")
    for hash in range(row + 1):
        print("#", end="")
    print("\n", end="")