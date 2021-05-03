#ifndef RETURN_CODE_H
#define RETURN_CODE_H

#include <stdint.h>
#include <iostream>
#include <map>

static std::map<uint32_t, std::string> gErrorStrings;

enum class System : uint8_t
{
    COMMON,
    CORE,
    DATA,
    INTERACTION
};

struct SubSystem
{
    constexpr operator uint8_t() const { return code; }
    constexpr explicit SubSystem(uint8_t i) : code(i) {}
private:
    uint8_t code;
};

struct ReturnCode
{
    System system;
    SubSystem subsystem{ 0 };
    uint8_t errorcode;
    uint32_t hash;

    constexpr ReturnCode(const System sys, const uint8_t code) : system(sys), errorcode(code), hash(Hash())
    {
    };
    
    constexpr ReturnCode(const System sys, const SubSystem sub, const uint8_t code) : system(sys), subsystem(sub), errorcode(code), hash(Hash())
    {
    };

    inline bool Success() const
    {
        return ( int( errorcode ) == 0 );
    };

    inline bool Failed() const
    {
        return ( int( errorcode ) != 0 );
    };

    inline constexpr uint32_t Hash() 
    {
        return  ( static_cast<uint8_t>( system )    << 16 ) +
                ( static_cast<uint8_t>( subsystem ) << 8 ) +
                ( static_cast<uint8_t>( errorcode ) );
    };

    inline std::string ToString() const
    {
        return gErrorStrings.find( hash )->second;
    };

    inline bool operator==( const ReturnCode& rhs ) const
    {
        return ( rhs.errorcode == errorcode && rhs.subsystem == subsystem && rhs.system == system );
    }
};

static constexpr const ReturnCode SUCCESS = ReturnCode(System::COMMON, 0x0000);
static constexpr const ReturnCode NOT_IMPLEMENTED = ReturnCode(System::COMMON, 0x0001);
static constexpr const ReturnCode NULLPTR_INPUT = ReturnCode(System::COMMON, 0x0002);


#endif