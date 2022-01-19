#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>

#include "funcs.h"
#include "defs.h"

int input = 0;
bool isRunning = true;

void *getInput(void *arg_win)
{
    WINDOW *win = (WINDOW *)arg_win;
    int ch = 0;
    while (isRunning)
    {
        ch = wgetch(win);
        if (ch != ERR)
        {
            input = ch;
        }
    }
    return NULL;
}

// TODO: Add Windows support
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    initscr();
    if (!has_colors())
    {
        endwin();
        fprintf(stderr, "ERROR: Your terminal does not support colored output!\n");
        exit(1);
    }
    start_color();
    cbreak();
    
    halfdelay(1);
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    init_pair(HEAD_COLOR, COLOR_WHITE, COLOR_GREEN);
    init_pair(BODY_COLOR, COLOR_WHITE, COLOR_YELLOW);
    init_pair(APPLE_COLOR, COLOR_WHITE, COLOR_RED);

    int width = 5;
    int height = 5;

    int window_width = width + 2;
    int window_height = height + 2;

    WINDOW *win = newwin(window_height, window_width, 0, 0);
    keypad(win, true);
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);

    Direction dir = {0, 1};
    Snake snake;

    snakeInit(&snake, width, height, (Point){1, 1});
    addSnakeEl(&snake, dir);
    addSnakeEl(&snake, dir);

    pthread_t th;

    pthread_create(&th, NULL, getInput, win);
    int localInput = 0;

    createApple(&snake, height, width);
    assert(snake.length > 1);
    while (!snake.isDead && isRunning)
    {
        wclear(win);
        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);

        if (isCollided(snake, dir, height, width))
        {
            snake.isDead = true;
            continue;
        }

        if (snake.coords[0].x + dir.x_move == snake.appleCoords.x && snake.coords[0].y + dir.y_move == snake.appleCoords.y)
        {
            addSnakeEl(&snake, dir);
            moveSnake(&snake, dir);
            createApple(&snake, height, width);
        }
        else
        {
            moveSnake(&snake, dir);
        }

        printField(win, snake);

        if (snake.length == snake.maxLen)
        {
            isRunning = false;
            continue;
        }

        usleep(500000);
        localInput = input;

        if (localInput == 'q' || localInput == 'Q')
        {
            snake.isDead = true;
            isRunning = false;
        }
        if (localInput == 'w' && dir.x_move != 1 && ABS(snake.coords[1].x - snake.coords[0].x) == 0)
        {
            dir.y_move = 0;
            dir.x_move = -1;
        }
        if (localInput == 's' && dir.x_move != -1 && ABS(snake.coords[1].x - snake.coords[0].x) == 0)
        {
            dir.y_move = 0;
            dir.x_move = 1;
        }
        if (localInput == 'a' && dir.y_move != 1 && ABS(snake.coords[1].y - snake.coords[0].y) == 0)
        {
            dir.x_move = 0;
            dir.y_move = -1;
        }
        if (localInput == 'd' && dir.y_move != -1 && ABS(snake.coords[1].y - snake.coords[0].y) == 0)
        {
            dir.x_move = 0;
            dir.y_move = 1;
        }
    }
    isRunning = false;
    pthread_join(th, NULL);
    int scrHeight = 0;
    int scrWidth = 0;
    getmaxyx(stdscr, scrHeight, scrWidth);

    delwin(win);
    if (snake.isDead)
    {
        mvprintw(scrHeight / 2, scrWidth / 2 - 6, "Game over!");
        mvprintw(scrHeight / 2 + 1, scrWidth / 2 - 11, "Press any key to exit.");
        nocbreak();
        cbreak();
        getch();
    }
    else
    {
        mvprintw(scrHeight / 2, scrWidth / 2 - 4, "You won!");
        mvprintw(scrHeight / 2 + 1, scrWidth / 2 - 11, "Press any key to exit.");
        nocbreak();
        cbreak();
        getch();
    }

    endwin();
    return 0;
}
