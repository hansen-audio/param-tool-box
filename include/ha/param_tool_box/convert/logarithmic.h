// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/log_scale.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"
#include <functional>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
/*
 * logarithmic
 */
template <typename RealType>
class logarithmic final
{
public:
    //-------------------------------------------------------------------------
    using value_type                    = RealType;
    using fn_precision                  = std::function<i32(value_type)>;
    static i32 const STANDARD_PRECISION = 2;

    logarithmic(value_type lo, value_type hi, value_type mid);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    typename detail::log_scale<value_type>::context_type context;
};

//-----------------------------------------------------------------------------
//  logarithmic
//-----------------------------------------------------------------------------
template <typename RealType>
logarithmic<RealType>::logarithmic(value_type lo, value_type hi, value_type mid)
{
    context = detail::log_scale<value_type>::create(lo, hi, mid);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename logarithmic<RealType>::value_type
logarithmic<RealType>::to_physical(value_type normalized) const
{
    normalized = clamp(normalized, value_type(0.), value_type(1.));

    return detail::log_scale<value_type>::scale(normalized, context);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename logarithmic<RealType>::value_type
logarithmic<RealType>::to_normalized(value_type physical) const
{
    physical = clamp(physical, context.min, context.max);

    return detail::log_scale<value_type>::scale_inverted(physical, context);
}

//-----------------------------------------------------------------------------
template <typename RealType>
string_type logarithmic<RealType>::to_string(value_type physical,
                                             fn_precision const& precision_func) const
{
    value_type const tmp_physical = clamp(physical, context.min, context.max);
    i32 const precision = precision_func ? precision_func(tmp_physical) : STANDARD_PRECISION;

    return to_string_with_precision(tmp_physical, precision);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename logarithmic<RealType>::value_type
logarithmic<RealType>::from_string(string_type const& value_string) const
{
    // TODO: Make this more robust to non-digit inputs.
    value_type const value = std::stod(value_string);

    return clamp(value, context.min, context.max);
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha