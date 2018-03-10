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
