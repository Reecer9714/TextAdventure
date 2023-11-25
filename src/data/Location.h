#ifndef Location_H
#define Location_H

#include <cstddef>
#include <list>
#include <string>
#include <unordered_map>

#include "Direction.h"
#include "Entity.h"
#include "core/ReturnCode.h"
#include "data/Direction.h"

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
    const Location* loc = nullptr;
    ExitStatus status = OPEN;
    bool visible = false;
    bool locked = false;
    bool stuck = false;
};

class Location
{
public:
    Location( const std::string& name );
    Location( const std::string& name, const std::string& desc );

    std::string getName() const;
    std::string getDesc() const;
    void setDesc( const std::string& desc );
    const std::unordered_map<Direction, Connection>& getExits() const;
    std::list<Entity*> getEntities();

    ReturnCode connectLocation( Direction d,
                                const Location* other,
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
    std::unordered_map<Direction, Connection> exits;
    std::list<Entity*> entities;
};

#endif