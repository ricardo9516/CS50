#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    //Compares scores to determine who will win
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int total = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyz"; //Variable that has all the alphabet matching the points positions
    //Cycle to check each letter, comparing it with each letter of the alphabet
    for (int i = 0; i < strlen(word); i++)
    {
        for (int j = 0; j < strlen(alphabet); j++)
        {
            if (tolower(word[i]) == alphabet[j]) //Needs to change to lower case so that is not case sensitive
            {
                total += POINTS[j];
            }
        }
    }
    return total;
}
