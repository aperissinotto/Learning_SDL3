#include "game.h"

int main(void)
{
    Game game;

    if (!Game_Init(&game))
    {
        return 1;
    }

    Game_Run(&game);

    Game_Shutdown(&game);

    return 0;
}