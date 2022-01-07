#ifndef FUNCS_H
#define FUNCS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#include "defs.h"

void clearField(char **field, int height, int width);
void drawSnake(char **field, Snake snake);
void printField(char **field, int heigth, int width);
void moveSnake(Snake *snake, struct Direction dir);
bool isCollided(Snake snake, struct Direction dir, int height, int width);
void createApple(Snake *snake, int height, int width);
void drawApple(char **field, Snake snake);
void addSnakeEl(Snake *snake);

#endif