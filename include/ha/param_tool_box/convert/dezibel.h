// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/detail/db_scale.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"

#include <functional>
#include <math.h>

namespace ha::ptb::convert {

//-----------------------------------------------------------------------------
/**
 * dezibel
 */
template <typename RealType>
class dezibel final
{
public:
    //-------------------------------------------------------------------------
    using value_type                    = RealType const;
    using mut_value_type                = RealType;
    using fn_precision                  = std::function<i32(value_type)>;
    static i32 const STANDARD_PRECISION = 2;

    dezibel(value_type min, value_type max);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    using scale_type = detail::db_scale<mut_value_type>;
    typename scale_type::context cx;
};

//-----------------------------------------------------------------------------
//  dezibel
//-----------------------------------------------------------------------------
template <typename RealType>
dezibel<RealType>::dezibel(value_type min, value_type max)
{
    cx = scale_type::create(min, max);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type dezibel<RealType>::to_physical(value_type normalized) const
{
    value_type clamped = clamp(normalized, cx.norm_min, cx.norm_max);

    return scale_type::scale(cx, clamped);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type dezibel<RealType>::to_normalized(value_type physical) const
{
    value_type clamped = clamp(physical, cx.db_min, cx.db_max);

    return scale_type::scale_inverted(cx, clamped);
}

//-----------------------------------------------------------------------------
template <typename RealType>
string_type dezibel<RealType>::to_string(value_type physical,
                                         fn_precision const& precision_func) const
{
    value_type const tmp_physical = clamp(physical, cx.db_min, cx.db_max);
    i32 const precision = precision_func ? precision_func(tmp_physical) : STANDARD_PRECISION;

    return tmp_physical <= cx.db_min ? "-inf" : to_string_with_precision(tmp_physical, precision);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type
dezibel<RealType>::from_string(string_type const& value_string) const
{
    // TODO: Make this more robust to non-digit inputs.
    value_type value = value_string == "-inf" ? cx.db_min : value_type(std::stod(value_string));

    return clamp(value, cx.db_min, cx.db_max);
}

//-----------------------------------------------------------------------------
} // namespace ha::ptb::convert
