#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

typedef struct Mouse
{
    float x;
    float y;

    bool leftPressed;
} Mouse;

#endif