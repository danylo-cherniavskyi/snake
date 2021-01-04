#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "someWinFuncs.h"
#include "funcs.h"
#include "settings.h"
#include "defs.h"

// typedef struct {
//     int length;
//     int **coords;
//     bool isDead;
// } Snake;

// struct Direction
// {
//     int x_move;
//     int y_move;
// };

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
    

    // snake.coords = 

    system("clear");
    printField(*field, HEIGTH, WIDTH);

    while (/*!kbhit()*/ !snake.isDead)
    {
        if (isCollided(snake, dir))
        {
            snake.isDead = true;
            break;
        }

        // coords[0] += dir.x_move;
        // coords[1] += dir.y_move;

        moveSnake(&snake, dir);

        system("clear");
        clearField(*field, HEIGTH, WIDTH);
        drawSnake(*field, snake, HEIGTH, WIDTH);
        printField(*field, HEIGTH, WIDTH);
        // printf("%c, %d:%d", ch, coords[0], coords[1]);

        usleep(500000);

        if (kbhit())
        {
            ch = getch();
            if (ch == 'w' && coords[0] > 0)
            {
                // coords[0]--;
                dir.y_move = 0;
                dir.x_move = -1;
            }
            if (ch == 's' && coords[0] < HEIGTH - 1)
            {
                // coords[0]++;
                dir.y_move = 0;
                dir.x_move = 1;
            }
            if (ch == 'a' && coords[1] > 0)
            {
                // coords[1]--;
                dir.x_move = 0;
                dir.y_move = -1;
            }
            if (ch == 'd' && coords[1] < WIDTH - 1)
            {
                // coords[1]++;
                dir.x_move = 0;
                dir.y_move = 1;
            }

            if (ch == 'q')
            {
                snake.isDead = true;
                break;
            }

            // else
            // {
            // fprintf(stdin, "%c", ' ');
            // }
        }
    }

    // printf("%d\n", ~2);

    return 0;
}
