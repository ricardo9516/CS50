#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lettersCount(string text);
int wordsCount(string text);
int sentencesCount(string text);
void ColemanLiauIndex(string text);

int main(void)
{
    string text = get_string("Text: "); //Gets the text from the user
    ColemanLiauIndex(text);
}

int lettersCount(string text) //Function to count words
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i])) //Checks if it is a letter from a-z or A-Z
        {
            count++;
        }
    }
    return count;
}

int wordsCount(string text) //Function to count words
{
    int count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32) //Checks for space
        {
            count++;
        }
    }
    return count;
}

int sentencesCount(string text) //Function to count sentences
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63) //Checks for space
        {
            count++;
        }
    }
    return count;
}


void ColemanLiauIndex(string text) //function to apply coleman liau formula
{
    float L = ((float) lettersCount(text) / wordsCount(text)) * 100;
    float S = ((float) sentencesCount(text) / wordsCount(text)) * 100;
    float index = .0588 * L - 0.296 * S - 15.8; //ColemanLiauIndex formula
    index = round(index);
    if (index < 1) //Checking limits
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}
