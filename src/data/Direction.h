#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <string>
#include <unordered_map>

constexpr size_t NUM_OF_DIRECTIONS = 10;

enum class Direction
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
    DOWN,
    INVALID
};

inline Direction getOppositeDirection( Direction& d )
{
    Direction r = Direction::INVALID;
    switch( d )
    {
    case Direction::NORTH: r = Direction::SOUTH; break;
    case Direction::SOUTH: r = Direction::NORTH; break;
    case Direction::EAST: r = Direction::WEST; break;
    case Direction::WEST: r = Direction::EAST; break;
    case Direction::NE: r = Direction::SW; break;
    case Direction::SE: r = Direction::NW; break;
    case Direction::NW: r = Direction::SE; break;
    case Direction::SW: r = Direction::NE; break;
    case Direction::UP: r = Direction::DOWN; break;
    case Direction::DOWN: r = Direction::UP; break;
    case Direction::INVALID:
    default: r = Direction::INVALID; break;
    }
    return r;
}

static std::unordered_map<std::string, Direction> const DirectionString = {
    { "north", Direction::NORTH },  { "n", Direction::NORTH },      { "south", Direction::SOUTH },
    { "s", Direction::SOUTH },      { "east", Direction::EAST },    { "e", Direction::EAST },
    { "west", Direction::WEST },    { "w", Direction::WEST },       { "northeast", Direction::NE },
    { "ne", Direction::NE },        { "southeast", Direction::SE }, { "se", Direction::SE },
    { "northwest", Direction::NW }, { "nw", Direction::NW },        { "southwest", Direction::SW },
    { "sw", Direction::SW },        { "up", Direction::UP },        { "u", Direction::UP },
    { "down", Direction::DOWN },    { "d", Direction::DOWN }
};

inline Direction tokenToDirection( std::string token )
{
    Direction d = Direction::INVALID;
    auto it = DirectionString.find( token );
    if( it != DirectionString.end() )
    {
        d = it->second;
    }

    return d;
}

#endif // __DIRECTION_H__