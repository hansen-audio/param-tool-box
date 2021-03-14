// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/db_scale.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"

#include <functional>
#include <math.h>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
/*
 * dezibel
 */
template <typename RealType>
class dezibel final
{
public:
    //-------------------------------------------------------------------------
    using value_type                    = RealType;
    using fn_precision                  = std::function<i32(value_type)>;
    static i32 const STANDARD_PRECISION = 2;

    dezibel(value_type min, value_type max);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    typename detail::db_scale<value_type>::context_type context;
};

//-----------------------------------------------------------------------------
//  dezibel
//-----------------------------------------------------------------------------
template <typename RealType>
dezibel<RealType>::dezibel(value_type min, value_type max)
{
    context = detail::db_scale<value_type>::create(min, max);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type dezibel<RealType>::to_physical(value_type normalized) const
{
    normalized = clamp(normalized, context.norm_min, context.norm_max);

    return detail::db_scale<value_type>::scale(normalized, context);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type dezibel<RealType>::to_normalized(value_type physical) const
{
    physical = clamp(physical, context.db_min, context.db_max);

    return detail::db_scale<value_type>::scale_inverted(physical, context);
}

//-----------------------------------------------------------------------------
template <typename RealType>
string_type dezibel<RealType>::to_string(value_type physical,
                                         fn_precision const& precision_func) const
{
    value_type const tmp_physical = clamp(physical, context.db_min, context.db_max);
    i32 const precision = precision_func ? precision_func(tmp_physical) : STANDARD_PRECISION;

    return tmp_physical <= context.db_min ? "-inf"
                                          : to_string_with_precision(tmp_physical, precision);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type
dezibel<RealType>::from_string(string_type const& value_string) const
{
    // TODO: Make this more robust to non-digit inputs.
    value_type const value =
        value_string == "-inf" ? context.db_min : value_type(std::stod(value_string));

    return clamp(value, context.db_min, context.db_max);
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha