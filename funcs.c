#include <stdio.h>
// #include "settings.h"
// #define CHARACTER(str) printf("\u" str)

// void printChars(char ch[], int amount)
// {
//     for (int i = 0; i < amount; i++)
//     {
//         printf("%s", ch);
//         // CHARACTER(number);
//     }
// }

void clearField(char *field, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            *(field+i*width+j) = ' ';
        }
    }
}

void printChars(char ch[], int amount)
{
    for (int i = 0; i < amount; i++)
    {
        printf("%s", ch);
    }
}

void printField(char *field, int heigth, int width)
{
    printf("\u250C");
    printChars("\u2500", width);
    printf("\u2510\n");

    for (int i = 0; i < heigth; i++)
    {
        printf("\u2502");
        for (int j = 0; j < width; j++)
        {
            if (*(field + width*i + j) == 'R')
                printf("\e[43m \e[0m" /**(field + width*i + j)*/);
            else if (*(field + width*i + j) == 'G')
                printf("\e[42m \e[0m" /**(field + width*i + j)*/);
            // else if (*(field + width*i + j) == 'C')
            //     printf("\e[49m " /**(field + width*i + j)*/);
            else
                printf("%c", *(field + width*i + j));
        }
        printf("\u2502\n");
    }

    printf("\u2514");
    printChars("\u2500", width);
    printf("\u2518\n");
}

void drawSnake(char *field, int coords[], int heigth, int width)
{
    *(field+coords[0]*width+coords[1]) = 'G';
}

