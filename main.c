#include "CSpeed.h"

#define AMENU_MAIN_THEME (SDL_Color) {AMENU_MAIN_BGCOLOR, 0xFF}, (SDL_Color) {AMENU_MAIN_TITLECOLOR2, 0xFF}, (SDL_Color) {AMENU_MAIN_TITLECOLOR1, 0xFF},  (SDL_Color) {AMENU_MAIN_TEXTCOLOR, 0xFF}

int mainLoop();

player runner;

int main(int argc, char* argv[])
{
    int launchCode = argc;
    if (argc > 0 && argv[0])
        launchCode = 0;
    launchCode = initSDL("C-Speed", ".", FONT_FILE_NAME, 32 * 20, 32 * 15, 24);
    SDL_DisplayMode dispMode;
    SDL_GetDesktopDisplayMode(0, &dispMode);
    SDL_SetWindowSize(mainWindow, dispMode.w, dispMode.h);
    while (!getKey())
    {
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);
        drawText("This is a test!", 0, 0, dispMode.w, dispMode.h, (SDL_Color) {0, 0, 0, 0xFF}, true);
    }
    initVector(&(runner.vect), 0, 0);
    initSprite(&(runner.spr), 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE, type_player);
    initPlayer(&runner, runner.spr, runner.vect);
    int gameCode = 0;
    bool quit = false;
    while(!quit)
    {
        switch(gameCode)
        {
        case 0:
            {
                int code = aMenu(tilesetTexture, 0, "C-Speed", (char*[3]) {"Start", "Options", "Quit"}, 3, 0, AMENU_MAIN_THEME, true, true, NULL);
                if (code == 3 || code == -1)
                    quit = true;
                gameCode = code + 1;
            }
            break;
        case 1:
            mainLoop();
            break;
        case 2:
            break;
        }
    }
    return launchCode;
}

int mainLoop()
{
    bool quit = false;
    while(!quit)
    {
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);
        quit = true;
    }
}
