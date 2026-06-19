#include "text.h"

static TTF_Font *font = NULL;

bool Text_Init(void)
{
    if (!TTF_Init())
    {
        return false;
    }

    font = TTF_OpenFont(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        18);

    return font != NULL;
}

void Text_Shutdown(void)
{
    if (font)
    {
        TTF_CloseFont(font);
    }

    TTF_Quit();
}

void Text_Draw(
    SDL_Renderer *renderer,
    const char *text,
    int x,
    int y)
{
    SDL_Color color =
    {
        255,
        255,
        255,
        255
    };

    SDL_Surface *surface =
        TTF_RenderText_Blended(
            font,
            text,
            0,
            color);

    if (!surface)
    {
        return;
    }

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(
            renderer,
            surface);

    SDL_FRect dst =
    {
        x,
        y,
        surface->w,
        surface->h
    };

    SDL_RenderTexture(
        renderer,
        texture,
        NULL,
        &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}