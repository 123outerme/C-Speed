#include "CSpeed.h"

vector* initVector(vector* vecPtr, double x, double y)
{
    vecPtr->x = x;
    vecPtr->y = y;
    return vecPtr;
}

void initPlayer(player* playerPtr, sprite spr, vector vect)
{
    playerPtr->spr = spr;
    playerPtr->vect = vect;
}

void initConfig(char* filePath)
{
    SC_UP = SDL_SCANCODE_W;
    SC_DOWN = SDL_SCANCODE_S;
    SC_LEFT = SDL_SCANCODE_A;
    SC_RIGHT = SDL_SCANCODE_D;
    SC_ATTACK = SDL_SCANCODE_LSHIFT;
    SC_INTERACT = SDL_SCANCODE_SPACE;
    SC_MENU = SDL_SCANCODE_ESCAPE;
    FPS = 60;
    soundVolume = MIX_MAX_VOLUME;
    musicVolume = MIX_MAX_VOLUME;
    saveConfig(filePath);
}

int aMenu(SDL_Texture* texture, int cursorID, char* title, char** optionsArray, const int options, int curSelect, SDL_Color bgColor, SDL_Color titleColorUnder, SDL_Color titleColorOver, SDL_Color textColor, bool border, bool isMain, void (*extraDrawing)(void))
{
    const int MAX_ITEMS = 9;
    if (curSelect < 1)
        curSelect = 1;
    if (options < 0)
        return ANYWHERE_QUIT;
    sprite cursor;
    initSprite(&cursor, TILE_SIZE, (curSelect + 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE, cursorID, 0, SDL_FLIP_NONE, (entityType) type_na);
    SDL_Event e;
    bool quit = false, settingsReset = false;
    int selection = -1;
    //While application is running
    while(!quit)
    {
        if (border)
            SDL_SetRenderDrawColor(mainRenderer, textColor.r, textColor.g, textColor.b, 0xFF);
        else
            SDL_SetRenderDrawColor(mainRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);

        SDL_RenderClear(mainRenderer);
        SDL_RenderFillRect(mainRenderer, NULL);
        SDL_SetRenderDrawColor(mainRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
        SDL_RenderFillRect(mainRenderer, &((SDL_Rect){.x = SCREEN_WIDTH / 128, .y = SCREEN_HEIGHT / 128, .w = 126 * SCREEN_WIDTH / 128, .h = 126 * SCREEN_HEIGHT / 128}));
        //background text (drawn first)
        drawText(title, 1 * TILE_SIZE + (5 - 2 * !isMain) * TILE_SIZE / 8, 11 * SCREEN_HEIGHT / 128, SCREEN_WIDTH, 119 * SCREEN_HEIGHT / 128, titleColorUnder, false);
        //foreground text
        drawText(title, 1 * TILE_SIZE + TILE_SIZE / (2 + 2 * !isMain) , 5 * SCREEN_HEIGHT / 64, SCREEN_WIDTH, 55 * SCREEN_HEIGHT / 64, titleColorOver, false);

        for(int i = 0; ((options <= MAX_ITEMS) ? i < options : i < MAX_ITEMS); i++)
	        drawText(optionsArray[i], 2 * TILE_SIZE + TILE_SIZE / 4, (5 + i) * TILE_SIZE, SCREEN_WIDTH, (HEIGHT_IN_TILES - (5 + i)) * TILE_SIZE, textColor, false);
        if (extraDrawing)
            (*extraDrawing)();

        //SDL_RenderFillRect(mainRenderer, &((SDL_Rect){.x = cursor.x, .y = cursor.y, .w = cursor.w, .h = cursor.w}));
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if(e.type == SDL_QUIT)
            {
                quit = true;
                selection = ANYWHERE_QUIT;
                //Mix_PlayChannel(-1, OPTION_SOUND, 0);
            }
            //User presses a key
            else if(e.type == SDL_KEYDOWN)
            {
                const Uint8* keyStates = SDL_GetKeyboardState(NULL);
                if (e.key.keysym.scancode == SC_UP && cursor.y > 5 * TILE_SIZE)
                {
                    cursor.y -= TILE_SIZE;
                    //Mix_PlayChannel(-1, PING_SOUND, 0);
                }

                if (e.key.keysym.scancode == SC_DOWN && cursor.y < (options + 4) * TILE_SIZE)
                {
                    cursor.y += TILE_SIZE;
                    //Mix_PlayChannel(-1, PING_SOUND, 0);
                }

                if (e.key.keysym.scancode == SC_INTERACT)
                {
                    selection = cursor.y / TILE_SIZE - 4;
                    quit = true;
                    //Mix_PlayChannel(-1, OPTION_SOUND, 0);
                }
                if (isMain && (keyStates[SDL_SCANCODE_LCTRL] || keyStates[SDL_SCANCODE_RCTRL]) && keyStates[SDL_SCANCODE_R] && !settingsReset)
                {
                    SC_UP = SDL_SCANCODE_W;
                    SC_DOWN = SDL_SCANCODE_S;
                    SC_LEFT = SDL_SCANCODE_A;
                    SC_RIGHT = SDL_SCANCODE_D;
                    SC_ATTACK = SDL_SCANCODE_LSHIFT;
                    SC_INTERACT = SDL_SCANCODE_SPACE;
                    SC_MENU = SDL_SCANCODE_ESCAPE;
                    saveConfig(CONFIG_FILEPATH);
                    //Mix_PlayChannel(-1, PLAYERHURT_SOUND, 0);
                    settingsReset = true;
                }
            }
        }
        drawATile(texture, cursor.tileIndex, cursor.x, cursor.y, TILE_SIZE, TILE_SIZE, 0, SDL_FLIP_NONE);
        SDL_RenderPresent(mainRenderer);
    }
    return selection;
}

void loadConfig(char* filePath)
{
    char* buffer = "";
    for(int i = 0; i < SIZE_OF_SCANCODE_ARRAY; i++)
    {
        readLine(filePath, i, &buffer);
        CUSTOM_SCANCODES[i] = strtol(buffer, NULL, 10);
    }
    readLine(filePath, SIZE_OF_SCANCODE_ARRAY, &buffer);
    FPS = strtol(strtok(buffer, "FPS="), NULL, 10);
    targetTime = calcWaitTime(FPS);
    readLine(filePath, SIZE_OF_SCANCODE_ARRAY + 1, &buffer);
    soundVolume = strtol(buffer, NULL, 10);
    Mix_Volume(-1, soundVolume);
    readLine(filePath, SIZE_OF_SCANCODE_ARRAY + 2, &buffer);
    musicVolume = strtol(buffer, NULL, 10);
    Mix_VolumeMusic(musicVolume);
}

void saveConfig(char* filePath)
{
    char* buffer = "";
    createFile(filePath);
    appendLine(filePath, intToString(SC_UP, buffer));
    appendLine(filePath, intToString(SC_DOWN, buffer));
    appendLine(filePath, intToString(SC_LEFT, buffer));
    appendLine(filePath, intToString(SC_RIGHT, buffer));
    appendLine(filePath, intToString(SC_INTERACT, buffer));
    appendLine(filePath, intToString(SC_MENU, buffer));
    appendLine(filePath, intToString(SC_ATTACK, buffer));
    char newBuffer[8];
    strcpy(newBuffer, "FPS=");
    appendLine(filePath, strcat(newBuffer, intToString(FPS, buffer)));
    appendLine(filePath, intToString(soundVolume, buffer));
    appendLine(filePath, intToString(musicVolume, buffer));
    //alternatively, we could iterate through all of CUSTOM_SCANCODES[].
}
