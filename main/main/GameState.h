#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "data\Entity.h"
#include "data\Location.h"

struct GameState
{
    bool running = true;
    Location* currentLocation;
    Entity player;
};

#endif