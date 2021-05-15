#include "Location.h"

#include <cstddef>

Location::Location( std::string name, std::string desc )
{
    this->name = name;
    this->description = desc;
};

std::string Location::getName()
{
    return this->name;
};

std::string Location::getDesc()
{
    return this->description;
};

std::array<Connection, NUM_OF_DIRECTIONS>* Location::getExits()
{
    return &exits;
};

std::list<Entity*> Location::getEntities()
{
    return this->entities;
};

ReturnCode Location::connectLocation( Direction d, Location* other, ExitStatus s, bool visible )
{
    if( other == nullptr )
    {
        return NULLPTR_INPUT;
    }

    std::array<Connection, NUM_OF_DIRECTIONS>::reference connection = this->exits.at( d );

    if( connection.connected )
    {
        return DUPLICATE_CONNECTION;
    }

    connection.loc = other;
    connection.status = s;
    connection.visible = visible;
    connection.connected = true;
    return SUCCESS;
};

void Location::disconnectLocation( Direction d )
{
    this->exits.at( d ).connected = false;
};

void Location::addEntity( Entity* e )
{
    this->entities.push_back( e );
};

void Location::removeEntity( Entity* e )
{
    this->entities.remove( e );
};