// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/process/ramp_processor.h"
#include <algorithm>

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
// ramp_processor
//------------------------------------------------------------------------
ramp_processor::ramp_processor(fn_value_queue queueFunc, value_type init)
: queue_func(std::move(queueFunc))
, current_ramp({init, init, 0})
, x(init)
{
    init_ramp(0);
}

//-----------------------------------------------------------------------------
ramp_processor::value_type ramp_processor::advance()
{
    if (current_ramp.is_done(x))
    {
        if (!more_ramps)
            return x;

        update_ramp();
    }

    x = current_ramp.advance(x);
    return x;
}

//-----------------------------------------------------------------------------
ramp_processor::value_type ramp_processor::get_value() const
{
    return x;
}

//-----------------------------------------------------------------------------
void ramp_processor::update_ramp()
{
    current_segment++;
    init_ramp(current_segment);
}

//-----------------------------------------------------------------------------
void ramp_processor::init_ramp(int index)
{
    int offset0         = 0;
    mut_value_type val0 = 0.;
    more_ramps          = queue_func ? queue_func(index++, offset0, val0) : false;
    if (!more_ramps)
        return;

    int offset1         = 0;
    mut_value_type val1 = 0.;
    more_ramps          = queue_func(index, offset1, val1);
    if (!more_ramps)
    {
        x            = val0;
        current_ramp = ramp(val0, val0, 0);
        return;
    }

    int const duration = (offset1 - offset0);
    current_ramp       = ramp(val0, val1, duration);
}

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha