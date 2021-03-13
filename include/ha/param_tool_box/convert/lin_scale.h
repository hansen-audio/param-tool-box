// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"

namespace ha {
namespace ptb {
namespace convert {
namespace detail {

//-----------------------------------------------------------------------------
/*
 *  lin_scale
 */
template <typename RealType>
class lin_scale final
{
public:
    //-------------------------------------------------------------------------
    using value_type = RealType;

    struct context_type
    {
        value_type norm_min = value_type(0.);
        value_type norm_max = value_type(0.);
        value_type phys_min = value_type(0.);
        value_type phys_max = value_type(0.);
    };

    static constexpr context_type create(value_type const min, value_type const max)
    {
        return {value_type(0.), value_type(1.), min, max};
    }

    static constexpr value_type scale(value_type const input, context_type const& context)
    {
        return input * context.phys_max + context.phys_min;
    }

    static constexpr value_type scale_inverted(value_type const input, context_type const& context)
    {
        return (input - context.phys_min) / (context.phys_max - context.phys_min);
    }
};

//-----------------------------------------------------------------------------
} // namespace detail
} // namespace convert
} // namespace ptb
} // namespace ha