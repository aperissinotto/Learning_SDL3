#include "ball.h"
#include "constants.h"

void Ball_Init(Ball *ball)
{
    ball->rect.w = BALL_SIZE;
    ball->rect.h = BALL_SIZE;

    ball->rect.x =
        (WINDOW_WIDTH / 2.0f)
        - (BALL_SIZE / 2.0f);

    ball->rect.y =
        (WINDOW_HEIGHT / 2.0f)
        - (BALL_SIZE / 2.0f);

    ball->vx = BALL_SPEED_X;
    ball->vy = BALL_SPEED_Y;
}

void Ball_Render(
    const Ball *ball,
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
        &ball->rect
    );
}

void Ball_Update(
    Ball *ball,
    float delta_time
)
{
    ball->rect.x +=
        ball->vx *
        delta_time;

    ball->rect.y +=
        ball->vy *
        delta_time;
    
    if (ball->rect.y <= 0)
    {
        ball->rect.y = 0;

        ball->vy = -ball->vy;
    }

    if (
    ball->rect.y +
    ball->rect.h >=
    WINDOW_HEIGHT
    )
    {
        ball->rect.y =
            WINDOW_HEIGHT
            - ball->rect.h;

        ball->vy = -ball->vy;
    }
}