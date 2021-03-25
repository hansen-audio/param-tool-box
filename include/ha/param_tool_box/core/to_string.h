// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"
#include <sstream>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
template <typename T>
std::string to_string_with_precision(T const value, i32 const precision = 6)
{
    T val = value;

#if _WIN32
    /**
     * On Windows 'out << std::fixed << val;' rounds whereas on macOS and Linux
     * it truncates. Therefore, round beforehand on Windows.
     */
    T const multiplier = pow(T(10), T(precision));
    val *= multiplier;
    val = std::trunc(val);
    val /= multiplier;
#endif

    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << val;
    return out.str();
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha