#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <algorithm>
#include <string>
#include <vector>

static inline std::string& ltrim( std::string& s )
{
    s.erase( s.begin(),
             std::find_if( s.begin(), s.end(), []( int ch ) { return std::isspace( ch ) == 0; } ) );
    return s;
}

static inline std::string& rtrim( std::string& s )
{
    s.erase( std::find_if( s.rbegin(), s.rend(), []( int ch ) { return std::isspace( ch ) == 0; } )
                 .base(),
             s.end() );
    return s;
}

static inline std::string& trim( std::string& s )
{
    return ltrim( rtrim( s ) );
}

static inline std::string& tolowercase( std::string& s )
{
    std::transform(
        s.begin(), s.end(), s.begin(), []( unsigned char c ) { return std::tolower( c ); } );
    return s;
}

#endif