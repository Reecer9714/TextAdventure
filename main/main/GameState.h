#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

#include "data/Entity.h"
#include "data/Location.h"

struct GameState
{
    bool running = true;
    Location* currentLocation;
    Entity player;
    std::vector<std::string> currentTokens;
};

#endif