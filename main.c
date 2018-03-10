#include "CSpeed.h"

int main(int argc, char* argv[])
{
    int launchCode = argc;
    if (argc > 0 && argv[0])
        launchCode = 0;
    launchCode = initSDL("C-Speed", ".", FONT_FILE_NAME, 32 * 20, 32 * 15, 24);
    SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mainRenderer);
    drawText("This is a test!", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (SDL_Color) {0, 0, 0, 0xFF}, true);
    waitForKey();
    return launchCode;
}
