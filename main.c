#include "CSpeed.h"

#define AMENU_MAIN_THEME (SDL_Color) {AMENU_MAIN_BGCOLOR, 0xFF}, (SDL_Color) {AMENU_MAIN_TITLECOLOR2, 0xFF}, (SDL_Color) {AMENU_MAIN_TITLECOLOR1, 0xFF},  (SDL_Color) {AMENU_MAIN_TEXTCOLOR, 0xFF}

#define TILESET_FILEPATH "tileset.png"

int mainLoop();

player runner;

int main(int argc, char* argv[])
{
    int launchCode = argc;
    if (argc > 0 && argv[0])
        launchCode = 0;
    launchCode = initSDL("C-Speed", TILESET_FILEPATH, FONT_FILE_NAME, TILE_SIZE * 20, TILE_SIZE * 15, 24);
    SDL_DisplayMode dispMode;
    SDL_GetDesktopDisplayMode(0, &dispMode);
    //SDL_SetWindowSize(mainWindow, dispMode.w, dispMode.h);
    while (!getKey())
    {
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);
        drawText("This is a test!", 0, 0, dispMode.w, dispMode.h, (SDL_Color) {0, 0, 0, 0xFF}, true);
    }
    initVector(&(runner.vect), 0, 0);
    initSprite(&(runner.spr), 0, screenHeight - 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, 0, SDL_FLIP_NONE, type_player);
    initPlayer(&runner, runner.spr, runner.vect);
    int gameCode = 0;
    if (!checkFile(CONFIG_FILEPATH, -1))
        initConfig(CONFIG_FILEPATH);
    else
        loadConfig(CONFIG_FILEPATH);
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
                gameCode = code;
            }
            break;
        case 1:
            mainLoop();
            quit = true;
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
    int exitCode = 0;
    SDL_Event e;
    while(!quit)
    {
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);

        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
                exitCode = -1;
            }
            else
                if(e.type == SDL_KEYDOWN)
                {
                    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
                    if (keyStates[SDL_SCANCODE_A] && runner.spr.x > 0)
                        runner.spr.x -= TILE_SIZE;
                    if (keyStates[SDL_SCANCODE_D] && runner.spr.x < screenWidth - TILE_SIZE)
                        runner.spr.x += TILE_SIZE;
                    if (keyStates[SDL_SCANCODE_ESCAPE])
                        quit = true;
                }
        }
        SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(mainRenderer, &((SDL_Rect) {.x = runner.spr.x, .y = runner.spr.y, .w = runner.spr.w, .h = runner.spr.h}));
        SDL_RenderPresent(mainRenderer);
    }
    return exitCode;
}
