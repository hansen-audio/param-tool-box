// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"
#include <sstream>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
template <typename T>
std::string to_string_with_precision(T const a_value, i32 const n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha