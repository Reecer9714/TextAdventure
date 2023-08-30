#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <cstddef>
#include <string>
#include <vector>

#include "core/GlobalError.h"
#include "data/Entity.h"
#include "data/Location.h"

struct GameState
{
    ReturnCode code{ SUCCESS };
    bool running = false;
    Location* currentLocation;
    Entity player;
    std::vector<std::string> currentTokens;
    size_t tokenLocation;

    ReturnCode TryMoveDirection( Direction d )
    {
        ReturnCode rc = NOT_IMPLEMENTED; // TODO new error
        if( d != Direction::INVALID )
        {
            Connection c = currentLocation->getExits().at( d );
            if( c.connected )
            {
                // TODO Locked or Visible check
                currentLocation = c.loc;
                rc = SUCCESS;
            }
        }
        return rc;
    }
};

#endif