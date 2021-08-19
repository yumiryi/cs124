//
//  randmst.c
//  Yumi Yi
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

// variables
int M = 40;
float minpenalty = INFINITY;
int prev[176];
int FS[176];
const char *text[] = {"Buffy", "the", "Vampire", "Slayer", "fans", "are", "sure", "to", "get", "their", "fix", "with", "the", "DVD",
"release", "of", "the", "show's", "first", "season.", "The", "three-disc", "collection",
"includes", "all", "12", "episodes", "as", "well", "as", "many", "extras.", "There", "is", "a", "collection",
"of", "interviews", "by", "the", "show's", "creator", "Joss", "Whedon", "in", "which", "he",
"explains", "his", "inspiration", "for", "the", "show", "as", "well", "as", "comments", "on", "the",
"various", "cast", "members.", "Much", "of", "the", "same", "material", "is", "covered", "in", "more",
"depth", "with", "Whedon's", "commentary", "track", "for", "the", "show's", "first", "two",
"episodes", "that", "make", "up", "the", "Buffy", "the", "Vampire", "Slayer", "pilot.", "The", "most",
"interesting", "points", "of", "Whedon's", "commentary", "come", "from", "his", "explanation",
"of", "the", "learning", "curve", "he", "encountered", "shifting", "from", "blockbuster", "films",
"like", "Toy", "Story", "to", "a", "much", "lower-budget", "television", "series.", "The", "first",
"disc", "also", "includes", "a", "short", "interview", "with", "David", "Boreanaz", "who", "plays", "the",
"role", "of", "Angel.", "Other", "features", "include", "the", "script", "for", "the", "pilot",
"episodes,", "a", "trailer,", "a", "large", "photo", "gallery", "of", "publicity", "shots", "and",
"in-depth", "biographies", "of", "Whedon", "and", "several", "of", "the", "show's", "stars,", "including",
"Sarah", "Michelle", "Gellar,", "Alyson", "Hannigan", "and", "Nicholas", "Brendon."};

// prototypes
int F(int i);
int length(int a, int b);
float extraspace(int a, int b);

// // main
int main(void)
{
    for (int i = 0; i < 176; i++)
    {
        prev[i] = -1;
        FS[i] = -1;
    }

    int result = F(1);
    printf("minimum penalty: %d\n", result);

    printf("breakpoints (last word per line):\n");
    for (int i = 0; i < 176; i++)
    {
        if (prev[i] != -1)
        {
            printf("%d, ", prev[i]);
        }
    }
    printf("\n");
}

// peek
int F(int i)
{
    if (length(i, 176) <= M)
    {
        FS[i] = 0;
        return 0;
    }
    else
    {
        for (int j = i; j <= 176; j++)
        {
            if (length(i,j) <= M)
            {
                float penalty;
                if (FS[j+1] != -1)
                {
                    penalty = pow(extraspace(i,j), 3.0) + FS[j+1];
                }
                else
                {
                    penalty = pow(extraspace(i,j), 3.0) + F(j+1);
                }
                if (penalty < minpenalty)
                {
                    minpenalty = penalty;
                    prev[i] = j;
                }
            }
        }

        return minpenalty;
    }
}

int length(int a, int b)
{
    int l = 0;
    for (int i = a; i <= b; i++)
    {
        l += strlen(text[i-1]);
    }
    l += b - a;
    return l;
}

float extraspace(int a, int b)
{
    int sum = 0;
    for (int i = a; i <= b; i++)
    {
        sum += strlen(text[i-1]);
    }
    int es = M - b + a - sum;
    float esx = es;
    return esx;
}