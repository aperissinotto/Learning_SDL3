#ifndef PADDLE_H
#define PADDLE_H

#include <SDL3/SDL.h>

typedef struct Paddle
{
    SDL_FRect rect;

    float speed;

} Paddle;

void Paddle_Init(
    Paddle *paddle,
    float x,
    float y,
    float width,
    float height
);

void Paddle_Render(
    const Paddle *paddle,
    SDL_Renderer *renderer
);

void Paddle_Update(
    Paddle *paddle,
    float direction,
    float delta_time
);

#endif