// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/linear.h"

namespace ha::ptb::convert {

//-----------------------------------------------------------------------------
/**
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
} // namespace ha::ptb::convert