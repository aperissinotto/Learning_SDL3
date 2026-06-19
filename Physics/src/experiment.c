#include "experiment.h"
static void RenderDebugInfo(Experiment *experiment);

bool Experiment_Init(Experiment *experiment)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Erro SDL_Init: %s\n", SDL_GetError());
        return false;
    }

    experiment->window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!experiment->window)
    {
        printf("Erro SDL_CreateWindow: %s\n", SDL_GetError());

        SDL_Quit();
        return false;
    }

    experiment->renderer = SDL_CreateRenderer(
        experiment->window,
        NULL);

    SDL_SetRenderVSync(
        experiment->renderer,
        1);

    if (!experiment->renderer)
    {
        printf("Erro SDL_CreateRenderer: %s\n",
               SDL_GetError());

        SDL_DestroyWindow(experiment->window);
        SDL_Quit();

        return false;
    }

    if (!Text_Init())
    {
        printf("Erro Text_Init\n");
        return false;
    }

    World_Init(
        &experiment->world);

    Ball_Init(
        &experiment->ball);

    experiment->lastCounter = SDL_GetPerformanceCounter();
    experiment->running = true;

    return true;
}

void Experiment_Run(Experiment *experiment)
{
    while (experiment->running)
    {
        Uint64 currentCounter =
            SDL_GetPerformanceCounter();

        experiment->deltaTime =
            (float)(currentCounter -
                    experiment->lastCounter) /
            SDL_GetPerformanceFrequency();

        experiment->lastCounter =
            currentCounter;

        Experiment_HandleEvents(experiment);

        Experiment_Update(experiment);

        Experiment_Render(experiment);
    }
}

void Experiment_Shutdown(Experiment *experiment)
{
    if (experiment->renderer)
    {
        SDL_DestroyRenderer(
            experiment->renderer);
    }

    if (experiment->window)
    {
        SDL_DestroyWindow(
            experiment->window);
    }

    Text_Shutdown();

    SDL_Quit();
}

static void RenderDebugInfo(Experiment *experiment)
{
    char buffer[128];
    int y = 10;

    snprintf(buffer,
             sizeof(buffer),
             "Velocidade Y: %.2f",
             experiment->ball.velY);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    float height =
        WINDOW_HEIGHT -
        (experiment->ball.y + experiment->ball.radius);

    snprintf(buffer,
             sizeof(buffer),
             "Altura: %.2f",
             height);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    snprintf(buffer,
             sizeof(buffer),
             "Gravidade: %.2f",
             experiment->world.gravity);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    snprintf(buffer,
             sizeof(buffer),
             "Massa: %.2f",
             experiment->ball.mass);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    float fps = 0.0f;

    if (experiment->deltaTime > 0.0f)
    {
        fps = 1.0f / experiment->deltaTime;
    }

    snprintf(buffer,
             sizeof(buffer),
             "FPS: %.2f",
             fps);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    float kineticEnergy =
        0.5f *
        experiment->ball.mass *
        experiment->ball.velY *
        experiment->ball.velY;

    snprintf(buffer,
             sizeof(buffer),
             "Energia Cinética: %.2f",
             kineticEnergy);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    snprintf(buffer,
         sizeof(buffer),
         "Frame Time: %.3f ms",
         experiment->deltaTime * 1000.0f);
    
    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);

    y += 25;

    snprintf(buffer,
         sizeof(buffer),
         "Delta: %.6f",
         experiment->deltaTime);

    Text_Draw(experiment->renderer,
              buffer,
              10,
              y);
}

void Experiment_Render(Experiment *experiment)
{
    SDL_SetRenderDrawColor(
        experiment->renderer,
        0,
        0,
        0,
        255);

    SDL_RenderClear(
        experiment->renderer);

    Ball_Render(
        &experiment->ball,
        experiment->renderer);

    RenderDebugInfo(
        experiment);

    SDL_RenderPresent(
        experiment->renderer);
}

void Experiment_HandleEvents(Experiment *experiment)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            experiment->running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_ESCAPE)
            {
                experiment->running = false;
            }
        }

        if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
            experiment->mouse.x = event.motion.x;
            experiment->mouse.y = event.motion.y;
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                experiment->mouse.leftPressed = true;
                if (Collision_PointCircle(
                        experiment->mouse.x,
                        experiment->mouse.y,
                        &experiment->ball))
                {
                    experiment->ball.grabbed = true;
                    experiment->ball.sleeping = false;

                    experiment->ball.velY = 0.0f;
                    experiment->ball.velX = 0.0f;
                }
            }
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                experiment->mouse.leftPressed = false;
                experiment->ball.grabbed = false;
            }
        }
    }
}

void Experiment_Update(
    Experiment *experiment)
{
    if (experiment->ball.grabbed)
    {
        experiment->ball.x =
            experiment->mouse.x;

        experiment->ball.y =
            experiment->mouse.y;
    }

    Ball_Update(
        &experiment->ball,
        &experiment->world,
        experiment->deltaTime);

    Collision_BallGround(&experiment->ball);
}