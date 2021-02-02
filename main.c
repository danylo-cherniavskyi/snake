#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "funcs.h"
#include "settings.h"
#include "defs.h"

#ifdef __linux__
    #include "someWinFuncs.h"
    #define CLEAR_SEQ "clear"
    #define GET_CHARACTER_FUNC getc(stdin)
#elif defined _WIN64 || defined _WIN32
    #include <conio.h>
    #define CLEAR_SEQ "cls"
    #define GET_CHARACTER_FUNC getch()
#endif

char field[HEIGTH][WIDTH] = { 0 };

int main(int argc, char const *argv[])
{
    clearField(*field, HEIGTH, WIDTH);
    char ch = ' ';
    struct Direction dir = {1, 0};

    Snake snake = {.maxLen = HEIGTH * WIDTH, .isDead = false};
    snake.coords = (int**)calloc(3, sizeof(int*));
    for (int i = 0; i < 3; i++)
    {
        snake.coords[i] = (int*)calloc(2, sizeof(int));
    }
    snake.appleCoords = (int*)calloc(2, sizeof(int));
    snake.length = 3;
    
    system(CLEAR_SEQ);
    createApple(&snake, *field, HEIGTH, WIDTH);
    drawSnake(*field, snake, HEIGTH, WIDTH);
    drawApple(*field, snake, WIDTH);
    printField(*field, HEIGTH, WIDTH);
    while (!snake.isDead)
    {
        if (isCollided(snake, dir))
        {
            snake.isDead = true;
            printf("Game over!\n");
            continue;
        }

        if (snake.coords[0][0]+dir.x_move == snake.appleCoords[0] && snake.coords[0][1]+dir.y_move == snake.appleCoords[1])
        {
            addSnakeEl(&snake, dir);
            moveSnake(&snake, dir);

            if (snake.maxLen == snake.length)
            {
                snake.isDead = true;
                system(CLEAR_SEQ);
                clearField(*field, HEIGTH, WIDTH);
                drawSnake(*field, snake, HEIGTH, WIDTH);
                printField(*field, HEIGTH, WIDTH);
                printf("You won!\n");

                continue;
            }

            createApple(&snake, *field, HEIGTH, WIDTH);
        }
        else
            moveSnake(&snake, dir);

        system(CLEAR_SEQ);
        clearField(*field, HEIGTH, WIDTH);
        drawSnake(*field, snake, HEIGTH, WIDTH);
        drawApple(*field, snake, WIDTH);
        printField(*field, HEIGTH, WIDTH);

        usleep(500000);

        while (kbhit())
        {
            ch = GET_CHARACTER_FUNC;
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
