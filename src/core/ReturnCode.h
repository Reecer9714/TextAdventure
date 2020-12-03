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
    uint8_t code;
    constexpr SubSystem(int y = 0) : code(y) {}
    constexpr operator uint8_t() const { return code; }
};

struct ErrorCode
{
    uint8_t code;
    constexpr ErrorCode(int y = 0) : code(y) {}
    constexpr operator uint8_t() const { return code; }
};

struct ReturnCode
{
    System system;
    SubSystem subsystem = 0;
    ErrorCode errorcode = 0;

    ReturnCode(System sys, ErrorCode code, std::string msg = "") : system(sys), errorcode(code)
    {
        std::cout << Hash() << std::endl;
        gErrorStrings.emplace(Hash(), msg);
    };
    ReturnCode(System sys, SubSystem sub, ErrorCode code, std::string msg = "") : system(sys), subsystem(sub), errorcode(code)
    {
        gErrorStrings.emplace(Hash(), msg);
    };

    inline bool Success() const
    {
        return (int(errorcode) == 0);
    };

    inline uint32_t Hash() const
    {
        return (static_cast<uint8_t>(system) << 16) +
            (int(subsystem) << 8) +
            (int(errorcode));
    };

    inline std::string ToString() const
    {
        return gErrorStrings.find(Hash())->second;
    };
};

static const ReturnCode SUCCESS = ReturnCode(System::COMMON, 0x0000, "Success");
static const ReturnCode NOT_IMPLEMENTED = ReturnCode(System::COMMON, 0x0001);
static const ReturnCode NULLPTR_INPUT = ReturnCode(System::COMMON, 0x0002);


#endif