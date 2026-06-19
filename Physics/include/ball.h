#ifndef BALL_H
#define BALL_H

#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>
#include "world.h"
#include "constants.h"

typedef struct Ball
{
    float mass;
    float radius;

    float x;
    float y;

    float startX;
    float startY;

    float velX;
    float velY;

    bool grabbed;
    bool sleeping;
} Ball;

void Ball_Init(Ball *ball);
void Ball_Render(const Ball *ball, SDL_Renderer *renderer);
void Ball_Update(Ball *ball, const World *world, float deltaTime);


#endif