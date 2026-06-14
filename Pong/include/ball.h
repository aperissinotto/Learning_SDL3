#ifndef BALL_H
#define BALL_H

#include <SDL3/SDL.h>

typedef struct Ball
{
    SDL_FRect rect;

    float vx;
    float vy;

} Ball;

void Ball_Init(Ball *ball);

void Ball_Update(
    Ball *ball,
    float delta_time
);

void Ball_Render(
    const Ball *ball,
    SDL_Renderer *renderer
);

void Ball_Reset(
    Ball *ball,
    float direction
);

#endif