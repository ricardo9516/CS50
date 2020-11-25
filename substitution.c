#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//Program to cipher an entered text with an entered Key of 26 characters

string ciphertext(string plaintext, string key); //Yotal letters

int main(int argc, string argv[])
{
    int rl = 0; //Repeated Letters
    if (argv[1] != 0)
    {
        for (int i = 0; i < strlen(argv[1]); i++) //check if a letter repeats itself
        {
            for (int j = 0; j < strlen(argv[1]); j++) //Loop through all the array
            {
                if (argv[1][i] == argv[1][j] && ((argv[1][i] > 64 && argv[1][i] < 91) || (argv[1][i] > 96
                                                 && argv[1][i] < 123))) //must be letters not case sensitive
                {
                    rl += 1;
                }
            }
        }
    }
    if (argv[1] == 0 || argv[2] != 0 || strlen(argv[1]) != 26 || rl != 26) // Check it has an argument of 26 characters unrepeated
    {
        printf("Incorrect Key, must be 26 characters, unrepeated.\n");
        return (1);
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: %s\n", ciphertext(plaintext, argv[1]));
        return (0);
    }
}

string ciphertext(string plaintext, string key)
{
    string ciphertext[1]; //ciphered word
    ciphertext[0] = plaintext;
    int pointer = 0; //To indicate where to search on the key
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] > 96 && plaintext[i] < 123)
        {
            pointer = plaintext[i] - 97; //point where to search in the key
            key[pointer] = tolower(key[pointer]);
            ciphertext[0][i] = key[pointer];
        }
        else if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            pointer = plaintext[i] - 65; //point where to search in the key}
            key[pointer] = toupper(key[pointer]);
            ciphertext[0][i] = key[pointer];
        }
    }
    return (ciphertext[0]);
}

