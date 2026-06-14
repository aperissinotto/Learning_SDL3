#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "paddle.h"
#include "ball.h"

typedef struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;

    Paddle player;
    Paddle cpu;

    Ball ball;

    int player_score;
    int cpu_score;
} Game;

bool Game_Init(Game *game);
void Game_Run(Game *game);
void Game_Shutdown(Game *game);
void Game_Render(Game *game);
void Game_Update(Game *game, float delta_time);
void Game_HandleEvents(Game *game);

#endif