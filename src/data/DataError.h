#ifndef DATAERROR_H
#define DATAERROR_H

#include "core/ReturnCode.h"

struct DataSubSystem : public SubSystem
{
    static const DataSubSystem
        LOCATION,
        ENTITY,
        ITEM;
};

constexpr const DataSubSystem
DataSubSystem::LOCATION{ 0 },
DataSubSystem::ENTITY{ 1 },
DataSubSystem::ITEM{ 2 };

static constexpr ReturnCode DUPLICATE_CONNECTION = ReturnCode(System::DATA, DataSubSystem::LOCATION, 0x0001);

#endif // DATAERROR_H