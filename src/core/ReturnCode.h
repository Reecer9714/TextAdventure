#ifndef RETURN_CODE_H
#define RETURN_CODE_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdint.h>
#include <string>
#include <string_view>

constexpr size_t SYSTEM_OFFSET = 16;
constexpr size_t SUBSYSTEM_OFFSET = 8;
constexpr const std::string_view DEFAULT_ERROR_MESSAGE = "Unknown Error: ";

template<typename Type, size_t Size>
using ErrorMessageArray = std::array<Type, Size>;
// NOLINTNEXTLINE (cppcoreguidelines-macro-usage) cant pass in std::array of unknown size
#define CastErrorMessageArray( array ) std::make_pair( ( array ).size(), ( array ).data() )

enum System : uint8_t
{
    COMMON,
    CORE,
    DATA,
    INTERACTION
};

struct ReturnCode
{
    const uint8_t system;
    const uint8_t subsystem;
    const uint8_t errorcode;

    constexpr ReturnCode( const uint8_t sys, const uint8_t code )
        : system( sys )
        , subsystem( 0 )
        , errorcode( code ){};

    constexpr ReturnCode( const uint8_t sys, const uint8_t sub, const uint8_t code )
        : system( sys )
        , subsystem( sub )
        , errorcode( code ){};

    ReturnCode( const ReturnCode& rc )
        : system( rc.system )
        , subsystem( rc.subsystem )
        , errorcode( rc.errorcode ){};

    inline bool Success() const { return ( errorcode == 0 ); };

    inline bool Failed() const { return ( errorcode != 0 ); };

    inline constexpr uint32_t Hash() const
    {
        return ( static_cast<uint8_t>( system ) << SYSTEM_OFFSET ) +
               ( static_cast<uint8_t>( subsystem ) << SUBSYSTEM_OFFSET ) +
               ( static_cast<uint8_t>( errorcode ) );
    };

    inline auto ToString() const
    {
        return std::to_string( system + ':' + subsystem + ':' + errorcode );
    };

    ReturnCode operator=( const ReturnCode& rc )
    {
        return ReturnCode( rc.system, rc.subsystem, rc.errorcode );
    }

    inline bool operator==( const ReturnCode& rhs ) const
    {
        return ( rhs.errorcode == errorcode && rhs.subsystem == subsystem && rhs.system == system );
    }
};

template<typename Type, size_t Size>
struct SubSystem
{
    constexpr explicit SubSystem( uint8_t i, ErrorMessageArray<Type, Size> msgs )
        : code( i )
        , messageArray( msgs )
    {
    }

    constexpr operator uint8_t() const { return code; }
    constexpr std::string_view ToString( uint8_t errorcode ) const
    {
        if( errorcode < messageArray->length() )
        {
            return messageArray[ errorcode - 1 ];
        }

        return DEFAULT_ERROR_MESSAGE;
    }

    constexpr ReturnCode CreateCode( const uint8_t sub, const uint8_t code ) const
    {
        return ReturnCode( code, sub, code );
    }

private:
    uint8_t code;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays) must be c array to be constexpr
    ErrorMessageArray<Type, Size> messageArray;
};

#endif