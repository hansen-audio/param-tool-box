// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <math.h>

namespace ha::ptb::convert::detail {

//-----------------------------------------------------------------------------
/**
 *  db_scale
 */
template <typename RealType>
class db_scale final
{
public:
    //-------------------------------------------------------------------------
    using value_type     = RealType const;
    using mut_value_type = RealType;

    struct context
    {
        mut_value_type norm_min = value_type(0.);
        mut_value_type norm_max = value_type(0.);
        mut_value_type db_min   = value_type(0.);
        mut_value_type db_max   = value_type(0.);
        mut_value_type inv_20   = value_type(0.);
    };

    static constexpr context create(value_type min, value_type max)
    {
        value_type const BASE           = value_type(10.);
        value_type const NOMRALIZED_MAX = value_type(1.);
        value_type const EXPONENT       = value_type(1. / 20.) * min;
        value_type const NOMRALIZED_MIN = pow(BASE, EXPONENT);

        return {NOMRALIZED_MIN, NOMRALIZED_MAX, min, max, value_type(1. / 20.)};
    }

    static constexpr value_type scale(context const& cx, value_type input)
    {
        return value_type(20.) * log10(input);
    }

    static constexpr value_type scale_inverted(context const& cx, value_type input)
    {
        return pow(value_type(10.), cx.inv_20 * input);
    }
};

//-----------------------------------------------------------------------------
} // namespace ha::ptb::convert::detail