// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"
#include "ramp.h"
#include <functional>

namespace ha::ptb {

//------------------------------------------------------------------------
/* ramp_processor
 *
 * This is a template class in order avoid std::function as it does a
 * virtual function call and potenial memory allocation.
 */
//------------------------------------------------------------------------
template <typename Func>
class ramp_processor
{
public:
    //--------------------------------------------------------------------
    using value_type     = ramp::value_type;
    using mut_value_type = ramp::mut_value_type;
    // using Func = std::function<bool(i32 /*index*/, i32& /*offset*/, mut_value_type& /*value*/)>;
    using fn_value_queue = Func;

    ramp_processor(fn_value_queue queue);

    value_type advance();
    value_type get_value() const;

    //--------------------------------------------------------------------
private:
    bool update_ramp();
    bool prepare_ramp(i32 index);

    ramp current_ramp;
    mut_value_type x          = value_type(0.);
    fn_value_queue queue_func = nullptr;
    i32 current_ramp_index    = 0;
    bool more_ramps           = true;
};

//------------------------------------------------------------------------
// ramp_processor
//------------------------------------------------------------------------
template <typename Func>
ramp_processor<Func>::ramp_processor(fn_value_queue queueFunc)
: queue_func(std::move(queueFunc))
, current_ramp({0., 0., 0})
, x(0.)
{
    more_ramps = prepare_ramp(0);
}

//-----------------------------------------------------------------------------
template <typename Func>
typename ramp_processor<Func>::value_type ramp_processor<Func>::advance()
{
    if (current_ramp.is_done(x))
    {
        if (!more_ramps)
            return x;

        more_ramps = update_ramp();
    }

    x = current_ramp.advance(x);
    return x;
}

//-----------------------------------------------------------------------------
template <typename Func>
typename ramp_processor<Func>::value_type ramp_processor<Func>::get_value() const
{
    return x;
}

//-----------------------------------------------------------------------------
template <typename Func>
bool ramp_processor<Func>::update_ramp()
{
    current_ramp_index++;
    return prepare_ramp(current_ramp_index);
}

//-----------------------------------------------------------------------------
template <typename Func>
bool ramp_processor<Func>::prepare_ramp(i32 index)
{
    i32 offset0         = 0;
    mut_value_type val0 = value_type(0.);
    if (!queue_func(index++, offset0, val0))
        return false;

    i32 offset1         = 0;
    mut_value_type val1 = value_type(0.);
    if (!queue_func(index, offset1, val1))
    {
        x            = val0;
        current_ramp = ramp(val0, val0, 0);
        return false;
    }

    i32 const duration = (offset1 - offset0);
    current_ramp       = ramp(val0, val1, duration);
    x                  = val0;
    return true;
}

//-----------------------------------------------------------------------------
} // namespace ha::ptb