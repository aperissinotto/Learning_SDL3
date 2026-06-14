#ifndef COLLISION_H
#define COLLISION_H

#include <SDL3/SDL.h>
#include <stdbool.h>

bool CheckCollision(
    const SDL_FRect *a,
    const SDL_FRect *b
);

#endif