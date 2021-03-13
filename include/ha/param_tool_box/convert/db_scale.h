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
 *  db_scale
 */
template <typename RealType>
class db_scale final
{
public:
    //-------------------------------------------------------------------------
    using value_type = RealType;

    struct context_type
    {
        value_type norm_min = value_type(0.);
        value_type norm_max = value_type(0.);
        value_type db_min   = value_type(0.);
        value_type db_max   = value_type(0.);
        value_type inv_20   = value_type(0.);
    };

    static constexpr context_type create(value_type const min, value_type const max)
    {
        value_type const BASE           = value_type(10.);
        value_type const NOMRALIZED_MAX = value_type(1.);
        value_type const EXPONENT       = value_type(1. / 20.) * min;
        value_type const NOMRALIZED_MIN = pow(BASE, EXPONENT);

        return {NOMRALIZED_MIN, NOMRALIZED_MAX, min, max, value_type(1. / 20.)};
    }

    static constexpr value_type scale(value_type const input, context_type const& context)
    {
        return value_type(20.) * log10(input);
    }

    static constexpr value_type scale_inverted(value_type const input, context_type const& context)
    {
        return pow(value_type(10.), context.INV_20 * input);
    }
};

//-----------------------------------------------------------------------------
} // namespace detail
} // namespace convert
} // namespace ptb
} // namespace ha