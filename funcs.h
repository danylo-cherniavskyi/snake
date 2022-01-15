#ifndef FUNCS_H
#define FUNCS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <assert.h>

#include "defs.h"

void printField(const Snake snake);
void moveSnake(Snake *snake, struct Direction dir);
bool isCollided(Snake snake, struct Direction dir, int height, int width);
void createApple(Snake *snake, int height, int width);
void addSnakeEl(Snake *snake);

#endif