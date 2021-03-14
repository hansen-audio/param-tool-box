// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/linear.h"

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