#include "paddle.h"

void Paddle_Init(
    Paddle *paddle,
    float x,
    float y,
    float width,
    float height
)
{
    paddle->rect.x = x;
    paddle->rect.y = y;

    paddle->rect.w = width;
    paddle->rect.h = height;

    paddle->speed = 400.0f;
}

void Paddle_Render(
    const Paddle *paddle,
    SDL_Renderer *renderer
)
{
    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255
    );

    SDL_RenderFillRect(
        renderer,
        &paddle->rect
    );
}

void Paddle_Update(
    Paddle *paddle,
    float direction,
    float delta_time
)
{
    paddle->rect.y +=
        direction *
        paddle->speed *
        delta_time;
}