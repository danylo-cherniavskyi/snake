#ifndef FUNCS_H
#define FUNCS_H

#include "defs.h"

void clearField(char *field, int height, int width);
void drawSnake(char *field, Snake snake, int heigth, int width);
void printField(char *field, int heigth, int width);
void moveSnake(Snake *snake, struct Direction dir);
bool isCollided(Snake snake, struct Direction dir);
void createApple(Snake *snake, char *field, int height, int width);
void drawApple(char *field, Snake snake, int width);
void addSnakeEl(Snake *snake, struct Direction dir);

#endif