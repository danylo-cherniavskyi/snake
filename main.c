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

void* getInput(void *arg)
{
    (void) arg;
    int ch = 0;
    while(isRunning)
    {
        ch = getch();
        if (ch != ERR)
        {
            input = ch;
        }
    }
    return NULL;
}

// TODO: More efficient way of working with dynamically allocated memory
// TODO: Make 'width' and 'height' be customizable
// TODO: Add Windows support
int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    initscr();
    if (!has_colors())
    {
        endwin();
        fprintf(stderr, "ERROR: Your terminal does not support colored output!\n");
        exit(1);
    }
    cbreak();
    start_color();
    halfdelay(1);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    box(stdscr, 0, 0);

    init_pair(HEAD_COLOR, COLOR_WHITE, COLOR_GREEN);
    init_pair(BODY_COLOR, COLOR_WHITE, COLOR_YELLOW);
    init_pair(APPLE_COLOR, COLOR_WHITE, COLOR_RED);

    int width = 0;
    int height = 0;

    getmaxyx(stdscr, height, width);

    height -= 2;
    width -= 2;
    
    Direction dir = {0, 1};

    Snake snake = {.maxLen = height * width, .isDead = false};
    snake.coords = (Point *)calloc(3, sizeof(Point));
    snake.length = 3;

    pthread_t th;

    pthread_create(&th, NULL, getInput, NULL);
    int localInput = 0;
    addSnakeEl(&snake);
    addSnakeEl(&snake);
    addSnakeEl(&snake);

    createApple(&snake, height, width);
    assert(snake.length > 1);
    while (!snake.isDead && isRunning)
    {
        clear();
        box(stdscr, 0, 0);
        if (isCollided(snake, dir, height, width))
        {
            snake.isDead = true;
            continue;
        }

        if (snake.coords[0].x+dir.x_move == snake.appleCoords.x && snake.coords[0].y + dir.y_move == snake.appleCoords.y)
        {
            addSnakeEl(&snake);
            moveSnake(&snake, dir);
            createApple(&snake, height, width);
        }
        else
        {
            moveSnake(&snake, dir);
        }

        printField(snake);

        usleep(200000);
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

    if (snake.isDead)
    {
        mvprintw(height / 2, width / 2 - 6, "Game over!");
        mvprintw(height / 2 + 1, width / 2 - 11, "Press any key to exit.");
        nocbreak();
        cbreak();
        getch();
    }
    else
    {
        mvprintw(height / 2, width / 2 - 4, "You won!");
        mvprintw(height / 2 + 1, width / 2 - 11, "Press any key to exit.");
        nocbreak();
        cbreak();
        getch();
    }

    endwin();
    return 0;
}
