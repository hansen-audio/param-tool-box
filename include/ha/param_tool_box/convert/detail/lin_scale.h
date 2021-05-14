// Copyright(c) 2021 Hansen Audio.

#pragma once

namespace ha {
namespace ptb {
namespace convert {
namespace detail {

//-----------------------------------------------------------------------------
/**
 *  lin_scale
 */
template <typename RealType>
class lin_scale final
{
public:
    //-------------------------------------------------------------------------
    using value_type     = RealType const;
    using mut_value_type = RealType;

    struct context
    {
        mut_value_type norm_min = value_type(0.);
        mut_value_type norm_max = value_type(0.);
        mut_value_type phys_min = value_type(0.);
        mut_value_type phys_max = value_type(0.);
    };

    static constexpr context create(value_type min, value_type const max)
    {
        return {value_type(0.), value_type(1.), min, max};
    }

    static constexpr value_type scale(context const& cx, value_type input)
    {
        return input * (cx.phys_max - cx.phys_min) + cx.phys_min;
    }

    static constexpr value_type scale_inverted(context const& cx, value_type input)
    {
        return (input - cx.phys_min) / (cx.phys_max - cx.phys_min);
    }
};

//-----------------------------------------------------------------------------
} // namespace detail
} // namespace convert
} // namespace ptb
} // namespace ha