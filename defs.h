#ifndef DEFS_H
#define DEFS_H

typedef struct {
    int x, y;
} Point;

typedef struct {
    int length;
    Point *coords;
    Point appleCoords;
    bool isDead;
    int maxLen;
} Snake;

typedef struct
{
    int x_move;
    int y_move;
} Direction;

#define ABS(x) (((x) < 0) ? (-x) : (x))
#define HEAD_COLOR 1
#define BODY_COLOR 2
#define APPLE_COLOR 3

#endif