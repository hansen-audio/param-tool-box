// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <algorithm>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
/*
 * @brief clamp, see also std::clamp which is available sind c++17
 */
template <class T>
constexpr T const& clamp(T const& v, T const& lo, T const& hi)
{
#if __cplusplus < 201700
    T const tmp_v = std::max(v, lo);
    return std::min(tmp_v, hi);
#else
    return std::clamp(v, lo, hi);
#endif
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha