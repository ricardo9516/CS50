#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//Program to check readability of a text according to Coleman-Liau index
//index = 0.0588 * L - 0.296 * S - 15.8
// L= Avg of letters in 100 words of the text
// S= Avg of sentences in 100 words of the text
double letters(string text); //Yotal letters
double words(string text); //Total words
double sentences(string text); //Total sentences
double round_nearest(double index); // Round final number

int main(void)
{
    string text = get_string("Text: "); //Ask for the text
    double L = 0;
    double S = 0;
    double index = 0;
    L = letters(text) / words(text) * 100;
    S = sentences(text) / words(text) * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", round_nearest(index));
    }

}

double letters(string text)
{
    int count = 0; //Count letters
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            count++;
        }
    }
    return (count);
}

double words(string text)
{
    int count = 1; //Count words, always start with one
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return (count);
}

double sentences(string text)
{
    int count = 0; //Count sentences
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            count++;
        }
    }
    return (count);
}

double round_nearest(double index)
{
    if ((index - (int)index) <= 0.5)
    {
        return(int)index;
    }
    else
    {
        return (int)index + 1;
    }

}
