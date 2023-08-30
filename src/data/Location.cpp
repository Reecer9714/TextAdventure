#include "Location.h"

#include "DataError.h"
#include "core/GlobalError.h"
#include "core/ReturnCode.h"
#include "data/Direction.h"
#include "data/Location.h"

Location::Location( std::string name, std::string desc )
    : name( std::move( name ) )
    , description( std::move( desc ) ){};

std::string Location::getName()
{
    return this->name;
};

std::string Location::getDesc()
{
    return this->description;
};

std::unordered_map<Direction, Connection>& Location::getExits()
{
    return exits;
};

std::list<Entity*> Location::getEntities()
{
    return this->entities;
};

ReturnCode Location::connectBothLocations( Direction d,
                                           Location* other,
                                           ExitStatus s,
                                           bool visible )
{
    ReturnCode rc = SUCCESS;
    rc = this->connectLocation( d, other, s, visible );
    if( rc.Success() )
    {
        rc = other->connectLocation( getOppositeDirection( d ), this, s, visible );
    }
    return rc;
};

ReturnCode Location::connectLocation( Direction d, Location* other, ExitStatus s, bool visible )
{
    if( other == nullptr )
    {
        return NULLPTR_INPUT;
    }

    const auto& [ connection, inserted ] = this->exits.try_emplace(
        d, Connection{ .loc = other, .status = s, .visible = visible, .connected = true } );
    if( !inserted )
    {
        return DUPLICATE_CONNECTION;
    }

    return SUCCESS;
};

void Location::disconnectLocation( Direction d )
{
    this->exits.erase( d );
};

void Location::addEntity( Entity* e )
{
    this->entities.push_back( e );
};

void Location::removeEntity( Entity* e )
{
    this->entities.remove( e );
};