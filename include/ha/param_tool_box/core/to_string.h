// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"
#include <math.h>
#include <sstream>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
template <typename T>
std::string to_string_with_precision(T const value, i32 const precision = 6)
{
    T val = value;

    T const multiplier = std::pow(T(10), T(precision));
    val *= multiplier;
    val = std::round(val);
    val /= multiplier;

    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << val;
    return out.str();
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha