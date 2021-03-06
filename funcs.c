#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "defs.h"
#include "settings.h"
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
                printf("\e[41m \e[0m" /**(field + width*i + j)*/);
            else if (*(field + width*i + j) == 'G')
                printf("\e[42m \e[0m" /**(field + width*i + j)*/);
            else if (*(field + width*i + j) == 'Y')
                printf("\e[43m \e[0m");
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

bool isCollided(Snake snake, struct Direction dir)
{
    bool res = false;
    if ((snake.coords[0][0] + dir.x_move) == HEIGTH || (snake.coords[0][0] + dir.x_move) == -1 ||
        (snake.coords[0][1] + dir.y_move) == WIDTH || (snake.coords[0][1] + dir.y_move) == -1)
        res = true;
    for (int i = 1; i < snake.length; i++)
    {
        if (snake.coords[0][0] + dir.x_move == snake.coords[i][0] && snake.coords[0][1] + dir.y_move == snake.coords[i][1])
        {
            res = true;
        }
    }

    return res;
}

void drawSnake(char *field, Snake snake, int heigth, int width)
{
    // *(field+coords[0]*width+coords[1]) = 'G';
    *(field + snake.coords[0][0]*width + snake.coords[0][1]) = 'G';
    for (int i = 1; i < snake.length; i++)
    {
        *(field + snake.coords[i][0]*width + snake.coords[i][1]) = 'Y';
    }
}

void drawApple(char *field, Snake snake, int width)
{
    *(field + snake.appleCoords[0]*width + snake.appleCoords[1]) = 'R';
}

int fillCoords(Snake *snake, int position, int coord_x, int coord_y)
{
    snake->coords[position] = (int*)calloc(2, sizeof(int));

    if (snake->coords[position] == NULL)
        return -1;
    
    snake->coords[position][0] = coord_x;
    snake->coords[position][1] = coord_y;
    return 0;
}

void copyIntArr(int dest[], int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = arr[i];
    }
}

void createApple(Snake *snake, char *field, int height, int width)
{
    srand(time(NULL));
    int appleXCoord = rand() % height,
        appleYCoord = rand() % width;
    bool isSet = false;

    while (!isSet)
    {
        isSet = true;
        for (int i = 0; i < snake->length; i++)
        {
            if (snake->coords[i][0] == appleXCoord && snake->coords[i][1] == appleYCoord)
            {
                appleXCoord = rand() % height;
                appleYCoord = rand() % width;
                isSet = false;
                break;
            }
        }
    }

    snake->appleCoords[0] = appleXCoord;
    snake->appleCoords[1] = appleYCoord;
}

void addSnakeEl(Snake *snake, struct Direction dir)
{
    int **tmp = NULL;
    snake->length++;
    tmp = (int**)realloc(snake->coords, snake->length*sizeof(int*));

    if (tmp)
        snake->coords = tmp;
    else
    {
        snake->length--;
        return;
    }
    snake->coords[snake->length-1] = (int*)calloc(2, sizeof(int));

    if (snake->coords[snake->length-1] == NULL)
    {
        tmp = (int**)realloc(snake->coords, (snake->length-1)*sizeof(int*));
        snake->length--;
        if (tmp)
            snake->coords = tmp;
        else
            return;
    }

    snake->coords[snake->length-1][0] = snake->coords[snake->length-2][0] + \
    (snake->coords[snake->length-2][0] - snake->coords[snake->length-3][0]);
    
    snake->coords[snake->length-1][1] = snake->coords[snake->length-2][1] + \
    (snake->coords[snake->length-2][1] - snake->coords[snake->length-3][1]);
}

void moveSnake(Snake *snake, struct Direction dir)
{
    int tmp1[2] = {0};
    int tmp2[2] = {0};

    copyIntArr(tmp1, snake->coords[0], 2);

    snake->coords[0][0] += dir.x_move;
    snake->coords[0][1] += dir.y_move;

    for (int i = 1; i < snake->length; i++)
    {
        copyIntArr(tmp2, snake->coords[i], 2);
        snake->coords[i][0] = tmp1[0];
        snake->coords[i][1] = tmp1[1];
        copyIntArr(tmp1, tmp2, 2);
    }
}