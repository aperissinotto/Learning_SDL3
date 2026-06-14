#include "game.h"
#include "constants.h"
#include "collision.h"

#include <stdio.h>

bool Game_Init(Game *game)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Erro SDL_Init: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!game->window)
    {
        printf("Erro SDL_CreateWindow: %s\n", SDL_GetError());

        SDL_Quit();
        return false;
    }

    game->renderer = SDL_CreateRenderer(
        game->window,
        NULL);

    if (!game->renderer)
    {
        printf("Erro SDL_CreateRenderer: %s\n",
               SDL_GetError());

        SDL_DestroyWindow(game->window);
        SDL_Quit();

        return false;
    }

    Paddle_Init(
        &game->player,
        50.0f,
        250.0f,
        20.0f,
        100.0f);

    Paddle_Init(
        &game->cpu,
        WINDOW_WIDTH - 50.0f - 20.0f,
        250.0f,
        20.0f,
        100.0f);

    Ball_Init(
        &game->ball);

    game->player_score = 0;
    game->cpu_score = 0;

    game->running = true;

    return true;
}

void Game_Run(Game *game)
{
    Uint64 previous_time =
        SDL_GetTicks();

    while (game->running)
    {
        Uint64 current_time =
            SDL_GetTicks();

        float delta_time =
            (current_time - previous_time) / 1000.0f;

        previous_time = current_time;

        Game_HandleEvents(game);

        Game_Update(
            game,
            delta_time);

        Game_Render(game);
    }
}

void Game_Shutdown(Game *game)
{
    if (game->renderer)
    {
        SDL_DestroyRenderer(
            game->renderer);
    }

    if (game->window)
    {
        SDL_DestroyWindow(
            game->window);
    }

    SDL_Quit();
}

void Game_Render(Game *game)
{
    SDL_SetRenderDrawColor(
        game->renderer,
        0,
        0,
        0,
        255);

    SDL_RenderClear(
        game->renderer);

    Paddle_Render(
        &game->player,
        game->renderer);

    Paddle_Render(
        &game->cpu,
        game->renderer);

    Ball_Render(
        &game->ball,
        game->renderer);

    SDL_RenderPresent(
        game->renderer);
}

void Game_Update(Game *game, float delta_time)
{
    const bool *keys =
        SDL_GetKeyboardState(NULL);

    float direction = 0.0f;

    if (keys[SDL_SCANCODE_W])
    {
        direction -= 1.0f;
    }

    if (keys[SDL_SCANCODE_S])
    {
        direction += 1.0f;
    }

    Paddle_Update(
        &game->player,
        direction,
        delta_time);

    float ball_center_y =
        game->ball.rect.y +
        game->ball.rect.h / 2.0f;

    float cpu_center_y =
        game->cpu.rect.y +
        game->cpu.rect.h / 2.0f;

    float cpu_direction = 0.0f;

    if (ball_center_y < cpu_center_y)
    {
        cpu_direction = -1.0f;
    }

    if (ball_center_y > cpu_center_y)
    {
        cpu_direction = 1.0f;
    }

    Paddle_Update(
        &game->cpu,
        cpu_direction,
        delta_time);

    Ball_Update(
        &game->ball,
        delta_time);

    if (CheckCollision(
            &game->ball.rect,
            &game->player.rect))
    {
        game->ball.rect.x =
            game->player.rect.x +
            game->player.rect.w;

        game->ball.vx =
            -game->ball.vx;
    }

    if (CheckCollision(
            &game->ball.rect,
            &game->cpu.rect))
    {
        game->ball.rect.x =
            game->cpu.rect.x -
            game->ball.rect.w;

        game->ball.vx =
            -game->ball.vx;
    }

    if (game->ball.rect.x < 0)
    {
        game->cpu_score++;
        printf(
            "Player: %d | CPU: %d\n",
            game->player_score,
            game->cpu_score);

        Ball_Reset(
            &game->ball,
            -1.0f);
    }

    if (game->ball.rect.x +
            game->ball.rect.w >
        WINDOW_WIDTH)
    {
        game->player_score++;
        printf(
            "Player: %d | CPU: %d\n",
            game->player_score,
            game->cpu_score);

        Ball_Reset(
            &game->ball,
            1.0f);
    }
}

void Game_HandleEvents(Game *game)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            game->running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_ESCAPE)
            {
                game->running = false;
            }
        }
    }
}