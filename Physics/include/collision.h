#ifndef COLLISION_H
#define COLLISION_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "ball.h"
#include "constants.h"

bool Collision_PointCircle(float pointX, float pointY, const Ball *ball);
void Collision_BallGround(Ball *ball);

#endif