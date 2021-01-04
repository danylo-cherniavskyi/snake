#ifndef FUNCS_H
#define FUNCS_H

#include "defs.h"

void clearField(char *field, int height, int width);
void drawSnake(char *field, Snake snake, int heigth, int width);
void printField(char *field, int heigth, int width);
void moveSnake(Snake *snake, struct Direction dir);
bool isCollided(Snake snake, struct Direction dir);

#endif