#ifndef DEFS_H
#define DEFS_H

typedef struct {
    int length;
    int **coords;
    bool isDead;
} Snake;


struct Direction
{
    int x_move;
    int y_move;
};

#endif