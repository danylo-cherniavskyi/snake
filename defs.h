#ifndef DEFS_H
#define DEFS_H

typedef struct {
    int length;
    int **coords;
    int *appleCoords;
    bool isDead;
    int maxLen;
} Snake;

struct Direction
{
    int x_move;
    int y_move;
};

#define ABS(x) (((x) < 0) ? (-x) : (x))
#define HEAD_COLOR 1
#define BODY_COLOR 2
#define APPLE_COLOR 3

#endif