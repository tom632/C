# TODO
from cs50 import get_float

while True:
    dollars = get_float('Change owed: ')
    if dollars > 0:
        cents = round(dollars * 100)
        coins = 0

        # Get quarters values (25¢)
        quarters = int(cents / 25)

        # Calulate dime value (10¢)
        dime = int((cents % 25) / 10)

        # Calulate nickels value (5¢)
        nickels = int(((cents % 25) % 10) / 5)

        # Calulate pennies value (1¢)
        pennies = int(((cents % 25) % 10) % 5)

        # if the cents is less than 25, the coins of quarters is zero
        coins = coins + quarters
        if dime > 0:
            coins = coins + dime
        if nickels > 0:
            coins = coins + nickels
        if pennies > 0:
            coins = coins + pennies

        print(coins)
        break