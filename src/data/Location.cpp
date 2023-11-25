#include "Location.h"

#include <sstream>

#include "DataError.h"
#include "core/GlobalError.h"
#include "core/ReturnCode.h"
#include "data/Direction.h"
#include "data/Location.h"

Location::Location( const std::string& name )
    : name( std::move( name ) ){};

Location::Location( const std::string& name, const std::string& desc )
    : name( std::move( name ) )
    , description( std::move( desc ) ){};

std::string Location::getName() const
{
    return this->name;
};

std::string Location::getDesc() const
{
    std::stringstream ss;
    ss << this->description << '\n';
    const auto north = exits.find( Direction::NORTH );
    const auto south = exits.find( Direction::SOUTH );
    const auto east = exits.find( Direction::EAST );
    const auto west = exits.find( Direction::WEST );
    const auto northeast = exits.find( Direction::NE );
    const auto southwest = exits.find( Direction::SW );
    const auto southeast = exits.find( Direction::SE );
    const auto northwest = exits.find( Direction::NW );

    ss << ( northwest != exits.end() ? "NW" : "  " );
    ss << ( north != exits.end() ? " N " : "   " );
    ss << ( northeast != exits.end() ? "NE" : "  " );
    ss << '\n';

    ss << ( northwest != exits.end() ? " \\" : "   " );
    ss << ( north != exits.end() ? "|" : " " );
    ss << ( northeast != exits.end() ? "/ " : "   " );
    ss << '\n';

    ss << ( west != exits.end() ? "W--" : "   " );
    ss << "X";
    ss << ( east != exits.end() ? "--E" : "   " );
    ss << '\n';

    ss << ( southwest != exits.end() ? " /" : "   " );
    ss << ( south != exits.end() ? "|" : " " );
    ss << ( southeast != exits.end() ? "\\ " : "   " );
    ss << '\n';

    ss << ( southwest != exits.end() ? "SW" : "  " );
    ss << ( south != exits.end() ? " S " : "   " );
    ss << ( southeast != exits.end() ? "SE" : "  " );
    ss << '\n';

    return ss.str();
};

void Location::setDesc( const std::string& desc )
{
    this->description = std::move( desc );
}

const std::unordered_map<Direction, Connection>& Location::getExits() const
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

ReturnCode Location::connectLocation( Direction d,
                                      const Location* other,
                                      ExitStatus s,
                                      bool visible )
{
    if( other == nullptr )
    {
        return NULLPTR_INPUT;
    }

    const auto& [ connection, inserted ] =
        this->exits.try_emplace( d, Connection{ .loc = other, .status = s, .visible = visible } );
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