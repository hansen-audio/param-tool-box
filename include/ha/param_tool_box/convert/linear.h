// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/detail/lin_scale.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"
#include <functional>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
/**
 * linear
 */
template <typename RealType>
class linear
{
public:
    //-------------------------------------------------------------------------
    using value_type                    = RealType const;
    using mut_value_type                = RealType;
    using fn_precision                  = std::function<i32(value_type)>;
    static i32 const STANDARD_PRECISION = 2;

    linear(value_type min, value_type max);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    using scale_type = detail::lin_scale<mut_value_type>;
    typename scale_type::context_type context;
};

//-----------------------------------------------------------------------------
//  linear
//-----------------------------------------------------------------------------
template <typename RealType>
linear<RealType>::linear(value_type min, value_type max)
{
    context = scale_type::create(min, max);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename linear<RealType>::value_type linear<RealType>::to_physical(value_type normalized) const
{
    value_type clamped = clamp(normalized, context.norm_min, context.norm_max);

    return scale_type::scale(clamped, context);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename linear<RealType>::value_type linear<RealType>::to_normalized(value_type physical) const
{
    value_type clamped = clamp(physical, context.phys_min, context.phys_max);

    return scale_type::scale_inverted(clamped, context);
}

//-----------------------------------------------------------------------------
template <typename RealType>
string_type linear<RealType>::to_string(value_type physical,
                                        fn_precision const& precision_func) const
{
    value_type tmp_physical = clamp(physical, context.phys_min, context.phys_max);
    i32 const precision     = precision_func ? precision_func(tmp_physical) : STANDARD_PRECISION;

    return to_string_with_precision(tmp_physical, precision);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename linear<RealType>::value_type
linear<RealType>::from_string(string_type const& value_string) const
{
    // TODO: Make this more robust to non-digit inputs.
    value_type const value = std::stod(value_string);

    return clamp(value, context.phys_min, context.phys_max);
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha