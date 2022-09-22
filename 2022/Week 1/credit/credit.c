#include <cs50.h>
#include <stdio.h>
#include <math.h>


string validateCard(long cardNumber);
void checkType(long cardNumber);
int digits(long num);
int sumDigits(int num);
int getFirstDigits(long num, int digits);

int main(void)
{
    long cardNumber = get_long("Number: ");
    validateCard(cardNumber);
    checkType(cardNumber);
}

//Function with Luhn’s Algorithm to validate card
string validateCard(long cardNumber)
{
    string validation;
    int otherDigitSum = 0;
    int remainingDigitSum = 0;
    int digit = 0;
    long num = cardNumber;
    for (int i = 1; i < digits(cardNumber) + 1; i++)
    {
        digit = num % 10;
        if (i % 2 == 1)
        {
            remainingDigitSum += digit;
        }
        else
        {
            if (digits(digit * 2) > 1)
            {
                otherDigitSum += sumDigits(digit * 2);
            }
            else
            {
                otherDigitSum += digit * 2;
            }

        }
        num /= 10;
    }
    int res = remainingDigitSum + otherDigitSum;
    if (res % 10 == 0)
    {
        validation = "VALID";
    }
    else
    {
        validation = "INVALID";
    }

    return validation;
}

void checkType(long cardNumber)
{
    string validation = "VALID";
    if (validateCard(cardNumber) == validation) //Verify if the card is valid
    {
        //Check which type it is based on given rules
        if (getFirstDigits(cardNumber, 1) == 4 && digits(cardNumber) >= 13 && digits(cardNumber) <= 16)
        {
            printf("VISA\n");
        }
        else if (getFirstDigits(cardNumber, 2) >= 51 && getFirstDigits(cardNumber, 2) <= 55 && digits(cardNumber) == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((getFirstDigits(cardNumber, 2) == 34 || getFirstDigits(cardNumber, 2) == 37) && digits(cardNumber) == 15)
        {
            printf("AMEX\n");
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


//Function to calculate total digits in a number
int digits(long num)
{
    int i = 0;
    while (num > 0)
    {
        num /= 10;
        i++;
    }
    return i;
}

//Function to sum digits
int sumDigits(int num)
{
    int i = 0;
    while (num > 0)
    {
        i += num % 10;
        num /= 10;
    }
    return i;
}

//Function to get first digits
int getFirstDigits(long num, int digits)
{
    while (num > pow(10, digits))
    {
        num /= 10;
    }
    return num;
}