#ifndef RETURN_CODE_H
#define RETURN_CODE_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdint.h>
#include <string>

constexpr size_t SYSTEM_OFFSET = 16;
constexpr size_t SUBSYSTEM_OFFSET = 8;
constexpr const char* const DEFAULT_ERROR_MESSAGE = "Unknown Error: ";

using ErrorMessageArray = std::pair<size_t, const char* const*>;
// NOLINTNEXTLINE (cppcoreguidelines-macro-usage) cant pass in std::array of unknown size
#define CastErrorMessageArray( array ) std::make_pair( ( array ).size(), ( array ).data() )

enum class System : uint8_t
{
    COMMON,
    CORE,
    DATA,
    INTERACTION
};

struct SubSystem
{
    constexpr explicit SubSystem( uint8_t i, ErrorMessageArray msgs = { 0, nullptr } )
        : code( i )
        , messageArray( msgs )
    {
    }

    constexpr operator uint8_t() const { return code; }
    const char* ToString( uint8_t errorcode ) const
    {
        if( messageArray.second != nullptr && errorcode < messageArray.first )
        {
            return messageArray.second[ errorcode ];
        }

        return DEFAULT_ERROR_MESSAGE;
    }

private:
    uint8_t code;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays) must be c array to be constexpr
    ErrorMessageArray messageArray;
};

struct GlobalSubSystem;

struct ReturnCode
{
    System system;
    SubSystem subsystem;
    uint8_t errorcode;

    constexpr ReturnCode( const System sys, const uint8_t code )
        : system( sys )
        , subsystem( 0 )
        , errorcode( code ){};

    constexpr ReturnCode( const System sys, const SubSystem sub, const uint8_t code )
        : system( sys )
        , subsystem( sub )
        , errorcode( code ){};

    inline bool Success() const { return ( errorcode == 0 ); };

    inline bool Failed() const { return ( errorcode != 0 ); };

    inline constexpr uint32_t Hash() const
    {
        return ( static_cast<uint8_t>( system ) << SYSTEM_OFFSET ) +
               ( static_cast<uint8_t>( subsystem ) << SUBSYSTEM_OFFSET ) +
               ( static_cast<uint8_t>( errorcode ) );
    };

    inline std::string ToString() const { return subsystem.ToString( errorcode ); };

    inline bool operator==( const ReturnCode& rhs ) const
    {
        return ( rhs.errorcode == errorcode && rhs.subsystem == subsystem && rhs.system == system );
    }
};

struct GlobalSubSystem : public SubSystem
{
    constexpr GlobalSubSystem( uint8_t n )
        : SubSystem( n ){};
    static const GlobalSubSystem COMMON;
};

inline constexpr const GlobalSubSystem GlobalSubSystem::COMMON{ 0 };

static constexpr const ReturnCode SUCCESS = ReturnCode( System::COMMON, 0x0000 );
static constexpr const ReturnCode NOT_IMPLEMENTED = ReturnCode( System::COMMON, 0x0001 );
static constexpr const ReturnCode NULLPTR_INPUT = ReturnCode( System::COMMON, 0x0002 );

#endif