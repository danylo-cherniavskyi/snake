#include "funcs.h"

void printField(WINDOW *win, const Snake snake)
{
    assert(snake.length > 0);

    wattron(win, COLOR_PAIR(HEAD_COLOR));
    mvwprintw(win, snake.coords[0].x + 1, snake.coords[0].y + 1, " ");
    wattroff(win, COLOR_PAIR(HEAD_COLOR));

    wattron(win, COLOR_PAIR(APPLE_COLOR));
    mvwprintw(win, snake.appleCoords.x + 1, snake.appleCoords.y + 1, " ");
    wattroff(win, COLOR_PAIR(APPLE_COLOR));

    for (int i = 1; i < snake.length; i++)
    {
        wattron(win, COLOR_PAIR(BODY_COLOR));
        mvwprintw(win, snake.coords[i].x + 1, snake.coords[i].y + 1, " ");
        wattroff(win, COLOR_PAIR(BODY_COLOR));
    }
}

bool isCollided(Snake snake, Direction dir, int height, int width)
{
    bool res = false;

    if ((snake.coords[0].x + dir.x_move) == height || (snake.coords[0].x + dir.x_move) == -1 ||
        (snake.coords[0].y + dir.y_move) == width || (snake.coords[0].y + dir.y_move) == -1)
        res = true;

    for (int i = 1; i < snake.length; i++)
    {
        if (snake.coords[0].x + dir.x_move == snake.coords[i].x && snake.coords[0].y + dir.y_move == snake.coords[i].y)
        {
            res = true;
        }
    }

    return res;
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
            if (snake->coords[i].x == appleXCoord && snake->coords[i].y == appleYCoord)
            {
                appleXCoord = rand() % height;
                appleYCoord = rand() % width;
                isSet = false;
                break;
            }
        }
    }

    snake->appleCoords.x = appleXCoord;
    snake->appleCoords.y = appleYCoord;
}

void snakeInit(Snake *snake, int fieldWidth, int fieldHeight, Point startPos)
{
    snake->isDead = false;
    snake->length = 0;
    snake->maxLen = fieldHeight * fieldWidth;
    snake->coords = calloc(snake->maxLen, sizeof(Point));
    snake->coords[0] = startPos;
    snake->length++;
}

void addSnakeEl(Snake *snake, const Direction dir)
{
    assert(snake->length < snake->maxLen);
    snake->length++;

    if (snake->length > 2)
    {
        snake->coords[snake->length - 1].x = snake->coords[snake->length - 2].x +
                                             (snake->coords[snake->length - 2].x - snake->coords[snake->length - 3].x);

        snake->coords[snake->length - 1].y = snake->coords[snake->length - 2].y +
                                             (snake->coords[snake->length - 2].y - snake->coords[snake->length - 3].y);
    }
    else
    {
        snake->coords[snake->length - 1] = (Point){snake->coords[0].x - dir.x_move, snake->coords[0].x - dir.y_move};
    }
}

void moveSnake(Snake *snake, Direction dir)
{
    Point tmp1 = {0};
    Point tmp2 = {0};

    assert(snake->length > 0);
    tmp1 = snake->coords[0];

    snake->coords[0].x += dir.x_move;
    snake->coords[0].y += dir.y_move;

    for (int i = 1; i < snake->length; i++)
    {
        tmp2 = snake->coords[i];
        snake->coords[i] = tmp1;
        tmp1 = tmp2;
    }
}