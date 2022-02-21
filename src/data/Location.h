#ifndef Location_H
#define Location_H

#include <cstddef>
#include <list>
#include <string>
#include <unordered_map>

#include "Direction.h"
#include "Entity.h"
#include "core/ReturnCode.h"

enum ExitStatus
{ // separate
    NO_EXIT,
    OPEN,
    CLOSED,
    LOCKED
};

class Location;

struct Connection
{
    Location* loc = nullptr;
    ExitStatus status = OPEN;
    bool visible = false;
    bool connected = false;
};

class Location
{
public:
    Location( std::string name, std::string desc );

    std::string getName();
    std::string getDesc();
    std::array<Connection, NUM_OF_DIRECTIONS>* getExits();
    std::list<Entity*> getEntities();

    ReturnCode connectLocation( Direction d,
                                Location* other,
                                ExitStatus s = OPEN,
                                bool visible = true );
    ReturnCode connectBothLocations( Direction d,
                                     Location* other,
                                     ExitStatus s = OPEN,
                                     bool visible = true );
    void disconnectLocation( Direction d );

    void addEntity( Entity* e );
    void removeEntity( Entity* e );

private:
    std::string name;
    std::string description;
    std::array<Connection, NUM_OF_DIRECTIONS> exits;
    std::list<Entity*> entities;
};

#endif