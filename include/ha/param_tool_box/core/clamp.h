// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <algorithm>

namespace ha::ptb::convert {

//-----------------------------------------------------------------------------
/*
 * @brief clamp, see also std::clamp which is available sind c++17
 */
template <class T>
constexpr T const clamp(T const& v, T const& lo, T const& hi)
{
    // For the case if lo > hi
    T const tmp_lo = std::min(lo, hi);
    T const tmp_hi = std::max(lo, hi);

#if __cplusplus < 201700
    T const tmp_v = std::max(v, tmp_lo);
    return std::min(tmp_v, tmp_hi);
#else
    return std::clamp(v, tmp_lo, tmp_hi);
#endif
}

//-----------------------------------------------------------------------------
} // namespace ha::ptb::convert