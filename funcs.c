#include "funcs.h"

void printField(const Snake snake)
{
    assert(snake.length > 0);

    attron(COLOR_PAIR(HEAD_COLOR));
    mvprintw(snake.coords[0][X] + 1, snake.coords[0][Y] + 1, " ");
    attroff(COLOR_PAIR(HEAD_COLOR));

    attron(COLOR_PAIR(APPLE_COLOR));
    mvprintw(snake.appleCoords[X] + 1, snake.appleCoords[Y] + 1, " ");
    attroff(COLOR_PAIR(APPLE_COLOR));

    for (int i = 1; i < snake.length; i++)
    {
        attron(COLOR_PAIR(BODY_COLOR));
        mvprintw(snake.coords[i][X] + 1, snake.coords[i][Y] + 1, " ");
        attroff(COLOR_PAIR(BODY_COLOR));
    }
}

bool isCollided(Snake snake, struct Direction dir, int height, int width)
{
    bool res = false;

    if ((snake.coords[0][0] + dir.x_move) == height || (snake.coords[0][0] + dir.x_move) == -1 ||
        (snake.coords[0][1] + dir.y_move) == width || (snake.coords[0][1] + dir.y_move) == -1)
        res = true;

    for (int i = 1; i < snake.length; i++)
    {
        if (snake.coords[0][0] + dir.x_move == snake.coords[i][0] && snake.coords[0][1] + dir.y_move == snake.coords[i][1])
        {
            res = true;
        }
    }

    return res;
}

void copyIntArr(int dest[], int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = arr[i];
    }
}

void createApple(Snake *snake, int height, int width)
{
    srand(time(NULL));
    int appleXCoord = rand() % height,
        appleYCoord = rand() % width;
    bool isSet = false;

    while (!isSet)
    { 
        isSet = true;
        for (int i = 0; i < snake->length; i++)
        {
            if (snake->coords[i][0] == appleXCoord && snake->coords[i][1] == appleYCoord)
            {
                appleXCoord = rand() % height;
                appleYCoord = rand() % width;
                isSet = false;
                break;
            }
        }
    }

    snake->appleCoords[0] = appleXCoord;
    snake->appleCoords[1] = appleYCoord;
}

void addSnakeEl(Snake *snake)
{
    int **tmp = NULL;
    snake->length++;
    tmp = (int**)realloc(snake->coords, snake->length*sizeof(int*));

    if (tmp)
        snake->coords = tmp;
    else
    {
        snake->length--;
        return;
    }
    snake->coords[snake->length-1] = (int*)calloc(2, sizeof(int));

    if (snake->coords[snake->length-1] == NULL)
    {
        tmp = (int**)realloc(snake->coords, (snake->length-1)*sizeof(int*));
        snake->length--;
        if (tmp)
            snake->coords = tmp;
        else
            return;
    }

    snake->coords[snake->length-1][0] = snake->coords[snake->length-2][0] + \
    (snake->coords[snake->length-2][0] - snake->coords[snake->length-3][0]);
    
    snake->coords[snake->length-1][1] = snake->coords[snake->length-2][1] + \
    (snake->coords[snake->length-2][1] - snake->coords[snake->length-3][1]);
}

void moveSnake(Snake *snake, struct Direction dir)
{
    int tmp1[2] = {0};
    int tmp2[2] = {0};

    copyIntArr(tmp1, snake->coords[0], 2);

    snake->coords[0][0] += dir.x_move;
    snake->coords[0][1] += dir.y_move;

    for (int i = 1; i < snake->length; i++)
    {
        copyIntArr(tmp2, snake->coords[i], 2);
        snake->coords[i][0] = tmp1[0];
        snake->coords[i][1] = tmp1[1];
        copyIntArr(tmp1, tmp2, 2);
    }
}