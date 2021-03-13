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
namespace detail {

//-----------------------------------------------------------------------------
/*
 *  log_scale
 */
template <typename RealType>
class log_scale final
{
public:
    //-------------------------------------------------------------------------
    using value_type = RealType;

    struct context_type
    {
        value_type y_norm = value_type(0.);
        value_type x_norm = value_type(0.);
        value_type min    = value_type(0.);
        value_type max    = value_type(0.);
        value_type mid    = value_type(0.);
        value_type a      = value_type(0.);
    };

    static constexpr context_type
    create(value_type const min, value_type const max, value_type const mid)
    {
        value_type const y_norm = (mid - min) / (max - min);
        value_type const x_norm = value_type(0.5);

        value_type const t =
            value_type(-1.0) /
            (((x_norm / y_norm - x_norm) / (x_norm - value_type(1.0))) - value_type(1.0));
        value_type const a = value_type(1.0) - value_type(1.0) / t;

        return {y_norm, x_norm, min, max, mid, a};
    }

    static constexpr value_type scale(value_type const input, context_type const& context)
    {
        value_type const output = input / (input + context.a * (input - value_type(1.0)));
        return output * (context.max - context.min) + context.min;
    }

    static constexpr value_type scale_inverted(value_type const input, context_type const& context)
    {
        value_type const output = (input - context.min) / (context.max - context.min);
        return value_type(-1.0) /
               ((value_type(1.0) / output - value_type(1.0)) / context.a - value_type(1.0));
    }
}; // namespace detail

//-----------------------------------------------------------------------------
} // namespace detail
} // namespace convert
} // namespace ptb
} // namespace ha