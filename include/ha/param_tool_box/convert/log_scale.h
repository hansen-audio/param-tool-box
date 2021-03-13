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

/*
 *  log_scale
 */
template <typename T>
class log_scale final
{
public:
    //--------------------------------------------------------------------
    struct context
    {
        T y_norm = 0.;
        T x_norm = 0.;
        T min    = 0.;
        T max    = 0.;
        T mid    = 0.;
        T a      = 0.;
    };

    static constexpr context create(T const min, T const max, T const mid)
    {
        const T y_norm = (mid - min) / (max - min);
        const T x_norm = T(0.5);

        const T t = T(-1.0) / (((x_norm / y_norm - x_norm) / (x_norm - T(1.0))) - T(1.0));
        const T a = T(1.0) - T(1.0) / t;

        return {y_norm, x_norm, min, max, mid, a};
    }

    static constexpr T scale(T const input, context const& ctxt)
    {
        T const output = input / (input + ctxt.a * (input - T(1.0)));
        return output * (ctxt.max - ctxt.min) + ctxt.min;
    }

    static constexpr T scale_inverted(T const input, context const& ctxt)
    {
        T const output = (input - ctxt.min) / (ctxt.max - ctxt.min);
        return T(-1.0) / ((T(1.0) / output - T(1.0)) / ctxt.a - T(1.0));
    }
}; // namespace detail

//------------------------------------------------------------------------
} // namespace detail
} // namespace convert
} // namespace ptb
} // namespace ha