// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/linear.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"

#include <algorithm>
#include <functional>
#include <math.h>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
/*
 * percent
 */
template <typename RealType>
class percent final : public linear<RealType>
{
public:
    //-------------------------------------------------------------------------
    percent()
    : linear<RealType>(0., 100.)
    {
    }
    //-------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha