# TODO
# import the get_int from cs50
from cs50 import get_int

while True:
    # get the height from the user
    height = get_int("Number of blocks? ")
    if height > 0 and height < 9:
        break
# loop around and set both sides of the pyrmid at the same time
for row in range(height):
    for space in range(height - row - 1, 0, -1):
        print(" ", end="")
    for hash in range(row+1):
        print("#", end="")
    print("  ", end="")
    for right_hash in range(row+1):
        print("#", end="")
    print("\n", end="")