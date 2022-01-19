#ifndef FUNCS_H
#define FUNCS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <assert.h>

#include "defs.h"

void printField(WINDOW *win, const Snake snake);
void moveSnake(Snake *snake, Direction dir);
bool isCollided(Snake snake, Direction dir, int height, int width);
void createApple(Snake *snake, int height, int width);
void addSnakeEl(Snake *snake, const Direction dir);
void snakeInit(Snake *snake, int fieldWidth, int fieldHeight, Point startPos);

#endif