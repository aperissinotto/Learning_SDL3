#include "collision.h"

bool Collision_PointCircle(
    float pointX,
    float pointY,
    const Ball *ball)
{
    float dx = pointX - ball->x;
    float dy = pointY - ball->y;

    return
        (dx * dx + dy * dy)
        <=
        (ball->radius * ball->radius);
}

void Collision_BallGround(Ball *ball)
{
    if (ball->y + ball->radius >= WINDOW_HEIGHT)
    {
        ball->y = WINDOW_HEIGHT - ball->radius;

        if (fabsf(ball->velY) < 10.0f)
        {
            ball->velY = 0.0f;
            ball->sleeping = true;
            return;
        }

        ball->velY *= -0.8f;
    }
}