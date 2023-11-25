#ifndef DATAERROR_H
#define DATAERROR_H

#include "core/ReturnCode.h"

constexpr const std::array LocationMessages = { "Duplicate Connection" };

static constexpr const SubSystem DataSubSystem{ System::DATA, LocationMessages };
enum DataSubSystemCode
{
    LOCATION,
    ENTITY,
    ITEM
};

static constexpr const auto DUPLICATE_CONNECTION =
    DataSubSystem.CreateCode( DataSubSystemCode::LOCATION, 1 );

#endif // DATAERROR_H