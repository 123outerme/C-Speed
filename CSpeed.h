#include "outermeSDL.h"

#define AMENU_MAIN_TEXTCOLOR  0x00, 0xB0, 0xDA
#define AMENU_MAIN_BGCOLOR 0xE4, 0xE9, 0xF3
#define AMENU_MAIN_TITLECOLOR1 0x4D, 0xD2, 0xFF
#define AMENU_MAIN_TITLECOLOR2 0x00, 0xAC, 0xE6

#define CONFIG_FILEPATH "assets/CSpeed.cfg"

#define calcWaitTime(x) x == 0 ? 0 : 1000 / x

typedef struct {
    double x;
    double y;
} vector;

typedef struct {
    sprite spr;
    vector vect;
} player;

vector* initVector(vector* vecPtr, double x, double y);
void initPlayer(player* playerPtr, sprite spr, vector vect);
void initConfig(char* filePath);
int aMenu(SDL_Texture* texture, int cursorID, char* title, char** optionsArray, const int options, int curSelect, SDL_Color bgColor, SDL_Color titleColorUnder, SDL_Color titleColorOver, SDL_Color textColor, bool border, bool isMain, void (*extraDrawing)(void));  //quick and dirty menu
void loadConfig(char* filePath);
void saveConfig(char* filePath);

#define SIZE_OF_SCANCODE_ARRAY 7
SDL_Scancode CUSTOM_SCANCODES[SIZE_OF_SCANCODE_ARRAY];
#define SC_UP CUSTOM_SCANCODES[0]
#define SC_DOWN CUSTOM_SCANCODES[1]
#define SC_LEFT CUSTOM_SCANCODES[2]
#define SC_RIGHT CUSTOM_SCANCODES[3]
#define SC_INTERACT CUSTOM_SCANCODES[4]
#define SC_MENU CUSTOM_SCANCODES[5]
#define SC_ATTACK CUSTOM_SCANCODES[6]

int FPS, targetTime;
