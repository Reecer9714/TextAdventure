#ifndef DATAERROR_H
#define DATAERROR_H

#include "core/ReturnCode.h"

constexpr const char* const LocationMessages[ 2 ] = { "Duplicate Connection",
                                                      "Unknown Connections" };

struct DataSubSystem : public SubSystem
{
    constexpr DataSubSystem( uint8_t n, ErrorMessageArray msgs = { 0, nullptr } )
        : SubSystem( n, msgs ){};
    static const DataSubSystem LOCATION, ENTITY, ITEM;
};

inline constexpr const DataSubSystem DataSubSystem::LOCATION{ 0ul, { 1, LocationMessages } },
    DataSubSystem::ENTITY{ 1 }, DataSubSystem::ITEM{ 2 };

static constexpr const ReturnCode DUPLICATE_CONNECTION =
    ReturnCode( System::DATA, DataSubSystem::LOCATION, 0x0001 );

#endif // DATAERROR_H