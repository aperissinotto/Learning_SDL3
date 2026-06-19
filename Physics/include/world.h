#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct World
{
    float gravity;
    float airResistance;
} World;

void World_Init(World *world);

#endif