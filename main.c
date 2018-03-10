#include "CSpeed.h"

int main(int argc, char* argv[])
{
    int launchCode = initSDL("C-Speed", ".", FONT_FILE_NAME, 32 * 20, 32 * 15, 24);
    drawText("This is a test!", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (SDL_Color) {0, 0, 0}, true);
    waitForKey();
    return launchCode;
}
