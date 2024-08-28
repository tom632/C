#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long n, odd, even;

    do
    {
        //get the users input
        n = get_long("please enter your card number ");
    }
    while (n < 0);
    {
        //set the variables to be used
        int checksum, evennumber, eventotal, oddtotal;

        //loop around to get the total for the even numbers
        for (even = n / 10, eventotal = 0; even > 0; even /= 100)
        {
            evennumber = even % 10;

            if ((2 * evennumber) > 9)
            {
                eventotal += (2 * evennumber) / 10;
                eventotal += ((2 * evennumber) % 10);
            }
            else
            {
                eventotal += ((2 * evennumber) % 10);
            }
        }

        //loop around to get the total for the odd numbers
        for (odd = n, oddtotal = 0; odd > 0; odd /= 100)
        {
            oddtotal += odd % 10;
        }

        checksum = eventotal + oddtotal;

        if (checksum % 10 == 0)
        {
            //Check for American Express
            if ((n >= 340000000000000 && n <= 350000000000000) || (n >= 370000000000000 && n <= 380000000000000))
            {
                printf("AMEX\n");
            }
            //Check for Mastercard
            else if (n >= 5100000000000000 && n <= 5600000000000000)
            {
                printf("MASTERCARD\n");
            }
            //check for visa
            else if ((n >= 4000000000000 && n <= 4200000000000) || (n >= 4000000000000000 && n <= 4200000000000000) || (n == 4222222222222))
            {
                printf("VISA\n");
            }
            //if none of the above card is invalid
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}