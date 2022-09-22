#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


bool validateKey(string key);
string cipherText(string text, string key);

int main(int argc, string argv[])
{
    if (argc != 2) //If the user types more or less than 2 arguments, then it will indicate how to do it correctly
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (validateKey(argv[1])) //Checking length and that is all letters
    {
        string text = get_string("plaintext:  ");
        printf("ciphertext: %s\n", cipherText(text, argv[1]));
        return 0;
    }
    else //Any other invalid attempt
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}


bool validateKey(string key) //Function to check length and that the key is only non repeated letters
{
    bool validation = true;
    if (strlen(key) != 26)
    {
        validation = false;
    }
    else
    {
        for (int i = 0; i < strlen(key); i++)
        {
            if (!(isalpha(key[i]))) //Will enter the condition if it is not an alphabetical character
            {
                validation = false;
            }
            else
            {
                int count = 0; //To count if it has been duplicated
                for (int j = 0; j < strlen(key); j++) //Check if a letter has been repeated
                {
                    if (key[i] == key[j])
                    {
                        count++;
                    }
                }
                if (count > 1)
                {
                    validation = false;
                }
            }
        }
    }
    return validation;
}

string cipherText(string text, string key) //Function to cipher the plain text using the substitution technique
{
    string cipheredText = text; //saved the text as the ciphered text to get a string of that length and then change each word
    int indexK = 0; //Saves the index for the letter in the key on each iteration of the loop
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i])) //for lower
            {
                indexK = (int) text[i];
                indexK -= 97;
                cipheredText[i] = tolower(key[indexK]);
            }
            else //for uppercase
            {
                indexK = (int) text[i];
                indexK -= 65;
                cipheredText[i] = toupper(key[indexK]);
            }
        }
        else
        {
            cipheredText[i] = text[i];
        }
    }
    return cipheredText;
}
