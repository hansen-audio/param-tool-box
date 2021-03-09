// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"

#include <algorithm>
#include <functional>
#include <math.h>

namespace ha {
namespace ptb {
namespace convert {

/*
 * linear
 */
template <typename RealType>
class linear
{
public:
    //-------------------------------------------------------------------------
    using value_type                           = RealType;
    using fn_precision                         = std::function<i32(value_type)>;
    static i32 const STANDARD_PRECISION        = 2;
    static constexpr value_type NOMRALIZED_MIN = 0.;
    static constexpr value_type NOMRALIZED_MAX = 1.;

    linear(value_type lo, value_type hi);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    value_type lo = 10.;
    value_type hi = 0.;
};

//-----------------------------------------------------------------------------
//  linear
//-----------------------------------------------------------------------------
template <typename RealType>
linear<RealType>::linear(value_type lo, value_type hi)
: lo(lo)
, hi(hi)
{
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename linear<RealType>::value_type linear<RealType>::to_physical(value_type normalized) const
{
    normalized = clamp(normalized, NOMRALIZED_MIN, NOMRALIZED_MAX);

    return normalized * hi + lo;
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename linear<RealType>::value_type linear<RealType>::to_normalized(value_type physical) const
{
    physical = clamp(physical, lo, hi);

    return (physical - lo) / (hi - lo);
}

//-----------------------------------------------------------------------------
template <typename RealType>
string_type linear<RealType>::to_string(value_type physical,
                                        fn_precision const& precision_func) const
{
    value_type const tmp_physical = clamp(physical, lo, hi);
    i32 const precision = precision_func ? precision_func(tmp_physical) : STANDARD_PRECISION;

    return to_string_with_precision(tmp_physical, precision);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename linear<RealType>::value_type
linear<RealType>::from_string(string_type const& value_string) const
{
    // TODO: Make this more robust to non-digit inputs.
    value_type const value = std::stod(value_string);

    return clamp(value, lo, hi);
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha