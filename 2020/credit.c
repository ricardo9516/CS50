#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Program to check types of credit cards and if its valid or not

int main(void)
{

    unsigned long long int credit; // Credit card number
    unsigned long long int creditV; //Credit assistant variable to validate credit
    int counter = 0; // Counter to get pair or odd and total digits
    int last; // Get last number
    int vnumber; // Validating number
    int American = 0;// Save first 4 digits for American Express
    int Master = 0; // Save first 2 digits for Mastercard
    int Visa = 0;//Save first number

    // Get credit card number rejecting letters or symbols
    credit = get_long("Number: ");



    //Validation loop
    while (credit >= 1)
    {
        counter++; //Total digits
        //last digit
        last = credit % 10;

        if (10 <= credit && credit < 100) //Get AmericanExpress
        {
            American = credit;
            Master = credit;
        }
        else if (1 <= credit && credit < 10) //Get Visa
        {
            Visa = credit;
        }
        //pair or odd
        if (counter % 2 == 0)
        {
            //pair
            last = last * 2;
            if ((last / 10) >= 1) // if it has 2 digits
            {
                while (last >= 1)  //sum of the 2 digits
                {
                    vnumber = vnumber + last % 10;
                    last = last / 10;
                }

            }
            else
            {
                //Acummulate
                vnumber = vnumber + last;
            }
        }
        else
        {
            //odd
            vnumber = vnumber + last;
        }
        //Next digit
        credit = credit / 10;

    } // end of while

    //printf("%i \n",vnumber);
    if (vnumber % 10 == 0)
    {

        if (counter == 15 && (American == 34 || American == 37)) // American
        {
            printf("AMEX\n");
        }
        else if (counter == 16 && Master > 50 && Master < 56) //Mastercard
        {
            printf("MASTERCARD\n");
        }
        else if (counter > 12 && counter < 17 && Visa == 4) // Visa
        {
            printf("VISA\n");
        }
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
