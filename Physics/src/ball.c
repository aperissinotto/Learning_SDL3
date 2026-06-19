#include "ball.h"

static void DrawFilledCircle(SDL_Renderer *renderer,
                             int centerX,
                             int centerY,
                             int radius);

void Ball_Init(Ball *ball)
{
    ball->mass = 10.0f;
    ball->radius = 25.0f;

    ball->x = WINDOW_WIDTH / 2.0f;
    ball->y = WINDOW_HEIGHT - ball->radius;

    ball->velX = 0.0f;
    ball->velY = 0.0f;

    ball->grabbed = false;
    ball->sleeping = false;
}

static void DrawFilledCircle(SDL_Renderer *renderer,
                             int centerX,
                             int centerY,
                             int radius)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if ((x * x) + (y * y) <= (radius * radius))
            {
                SDL_RenderPoint(renderer,
                                centerX + x,
                                centerY + y);
            }
        }
    }
}

void Ball_Render(const Ball *ball,
                 SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer,
                           255,
                           255,
                           255,
                           255);

    DrawFilledCircle(renderer,
                     (int)ball->x,
                     (int)ball->y,
                     (int)ball->radius);
}

void Ball_Update(
    Ball *ball,
    const World *world,
    float deltaTime)
{
    if (ball->grabbed || ball->sleeping)
    {
        return;
    }

    ball->velY +=
        world->gravity * deltaTime;

    ball->velY -=
        ball->velY *
        world->airResistance *
        deltaTime;

    ball->y +=
        ball->velY * deltaTime;
}