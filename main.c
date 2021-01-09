#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "someWinFuncs.h"
#include "funcs.h"
#include "settings.h"
#include "defs.h"

char field[HEIGTH][WIDTH] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

int main(int argc, char const *argv[])
{
    // system("clear");
    // field[0][4] = 'G';
    // printField(*field, HEIGTH, WIDTH);

    // for (int i = 1; i < 12; i++)
    // {
    //     // sleep(1);
    //     usleep(500000);
    //     system("clear");
    //     if (i > 2)
    //         field[i-3][4] = ' ';
    //     if (i > 1)
    //         field[i-2][4] = 'R';
    //     field[i-1][4] = 'R';
    //     field[i][4] = 'G';

    //     printField(*field, HEIGTH, WIDTH);
    // }

    char ch = ' ';
    int coords[] = {1, 1};
    struct Direction dir = {1, 0};

    Snake snake = {.isDead = false};
    snake.coords = (int**)calloc(3, sizeof(int*));
    for (int i = 0; i < 3; i++)
    {
        snake.coords[i] = (int*)calloc(2, sizeof(int));
    }
    snake.length = 3;
    

    system("clear");
    printField(*field, HEIGTH, WIDTH);
    while (!snake.isDead)
    {
        if (isCollided(snake, dir))
        {
            snake.isDead = true;
            break;
        }

        moveSnake(&snake, dir);

        system("clear");
        clearField(*field, HEIGTH, WIDTH);
        drawSnake(*field, snake, HEIGTH, WIDTH);
        printField(*field, HEIGTH, WIDTH);

        usleep(500000);

        while (kbhit())
        {
            ch = getc(stdin);
            if (ch == 'w' && dir.x_move != 1 && ABS(snake.coords[1][0] - snake.coords[0][0]) == 0)
            {
                dir.y_move = 0;
                dir.x_move = -1;
            }
            if (ch == 's' && dir.x_move != -1 && ABS(snake.coords[1][0] - snake.coords[0][0]) == 0)
            {
                dir.y_move = 0;
                dir.x_move = 1;
            }
            if (ch == 'a' && dir.y_move != 1 && ABS(snake.coords[1][1] - snake.coords[0][1]) == 0)
            {
                dir.x_move = 0;
                dir.y_move = -1;
            }
            if (ch == 'd' && dir.y_move != -1 && ABS(snake.coords[1][1] - snake.coords[0][1]) == 0)
            {
                dir.x_move = 0;
                dir.y_move = 1;
            }

            if (ch == 'q')
            {
                snake.isDead = true;
                break;
            }
        }
    }

    printf("\n");

    return 0;
}
