#ifndef Location_H
#define Location_H

#include <string>
#include <list>
#include <unordered_map>

#include "DataError.h"
#include "Entity.h"

#define NUM_OF_DIRECTIONS 10

enum Direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NE,
    SE,
    NW,
    SW,
    UP,
    DOWN
};

enum ExitStatus
{ //separate
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
    std::string name;
    std::string description;
    Connection exits[NUM_OF_DIRECTIONS];
    std::list<Entity*> entities;

public:

    Location(std::string name, std::string desc);

    ~Location();

    std::string getName();
    std::string getDesc();
    Connection* getExits();
    std::list<Entity*> getEntities();

    ReturnCode connectLocation(Direction d, Location* other, ExitStatus s = OPEN, bool visible = true);
    void disconnectLocation(Direction d);

    void addEntity(Entity* e);
    void removeEntity(Entity* e);

private:
    Location();
};

#endif