#ifndef __GLOBALERROR_H__
#define __GLOBALERROR_H__

#include "ReturnCode.h"

constexpr const std::array GlobalMessages = { "Success", "Not Implemented", "Nullptr Input" };

static constexpr const SubSystem GlobalSubSystem{ System::COMMON, GlobalMessages };

static constexpr const auto SUCCESS = GlobalSubSystem.CreateCode( 0, 0 );
static constexpr const auto NOT_IMPLEMENTED = GlobalSubSystem.CreateCode( 0, 1 );
static constexpr const auto NULLPTR_INPUT = GlobalSubSystem.CreateCode( 0, 2 );

#endif // __GLOBALERROR_H__