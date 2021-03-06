// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"
#include <math.h>
#include <sstream>

namespace ha::ptb::convert {

//-----------------------------------------------------------------------------
template <typename T>
std::string to_string_with_precision(T const value, i32 const precision = 6)
{
    T val = value;

    T const multiplier = pow(T(10), T(precision));
    val *= multiplier;
    val = round(val);
    val /= multiplier;

    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << val;
    return out.str();
}

//-----------------------------------------------------------------------------
} // namespace ha::ptb::convert