#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <string>

constexpr size_t NUM_OF_DIRECTIONS = 10;

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
    DOWN,
    INVALID
};

inline Direction getOppositeDirection( Direction& d )
{
    Direction r = INVALID;
    switch( d )
    {
    case NORTH: r = SOUTH; break;
    case SOUTH: r = NORTH; break;
    case EAST: r = WEST; break;
    case WEST: r = EAST; break;
    case NE: r = SW; break;
    case SE: r = NW; break;
    case NW: r = SE; break;
    case SW: r = NE; break;
    case UP: r = DOWN; break;
    case DOWN: r = UP; break;
    case INVALID:
    default: r = INVALID; break;
    }
    return r;
}

inline Direction tokenToDirection( std::string token )
{
    Direction d = INVALID;
    if( token == "north" || token == "n" )
    {
        d = NORTH;
    }
    else if( token == "south" || token == "s" )
    {
        d = SOUTH;
    }
    else if( token == "east" || token == "r" )
    {
        d = EAST;
    }
    else if( token == "west" || token == "w" )
    {
        d = WEST;
    }
    else if( token == "northeast" || token == "ne" )
    {
        d = NE;
    }
    else if( token == "southeast" || token == "se" )
    {
        d = SE;
    }
    else if( token == "northwest" || token == "nw" )
    {
        d = NW;
    }
    else if( token == "southwest" || token == "sw" )
    {
        d = SW;
    }
    else if( token == "up" || token == "u" )
    {
        d = UP;
    }
    else if( token == "down" || token == "d" )
    {
        d = DOWN;
    }

    return d;
}

#endif // __DIRECTION_H__