#ifndef __GLOBALERROR_H__
#define __GLOBALERROR_H__

#include "ReturnCode.h"

constexpr const std::array<const char*, 3> GlobalMessages = { "Success",
                                                              "Not Implemented",
                                                              "Nullptr Input" };

struct GlobalSubSystem : public SubSystem
{
    constexpr GlobalSubSystem( uint8_t n, ErrorMessageArray msgs = { 0, nullptr } )
        : SubSystem( n, msgs ){};
    static const GlobalSubSystem COMMON;
};

inline constexpr const GlobalSubSystem GlobalSubSystem::COMMON{
    0, CastErrorMessageArray( GlobalMessages )
};

static constexpr const ReturnCode SUCCESS = ReturnCode( System::COMMON, 0 );
static constexpr const ReturnCode NOT_IMPLEMENTED = ReturnCode( System::COMMON, 1 );
static constexpr const ReturnCode NULLPTR_INPUT = ReturnCode( System::COMMON, 2 );

#endif // __GLOBALERROR_H__