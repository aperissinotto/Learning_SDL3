#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "world.h"
#include "ball.h"
#include "mouse.h"
#include "constants.h"
#include "collision.h"
#include "text.h"
#include <stdio.h>

typedef struct Experiment
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;

    float deltaTime;

    Uint64 lastCounter;

    World world;
    Ball ball;
    Mouse mouse;

} Experiment;

bool Experiment_Init(Experiment *experiment);
void Experiment_Run(Experiment *experiment);
void Experiment_Shutdown(Experiment *experiment);
void Experiment_Render(Experiment *experiment);
void Experiment_HandleEvents(Experiment *experiment);
void Experiment_Update(Experiment *experiment);

#endif