#ifndef DEFS_H
#define DEFS_H

typedef struct {
    int length;
    int **coords;
    int *appleCoords;
    bool isDead;
} Snake;

struct Direction
{
    int x_move;
    int y_move;
};

#define ABS(x) (((x) < 0) ? (-x) : (x))

#endif