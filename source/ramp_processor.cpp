// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/process/ramp_processor.h"
#include <algorithm>

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
// RampProcessor
//------------------------------------------------------------------------
RampProcessor::RampProcessor(fn_value_queue queueFunc, value_type init)
: queue_func(std::move(queueFunc))
, ramp({init, init, 0})
, x(init)
{
    initRamp(0);
}

//-----------------------------------------------------------------------------
RampProcessor::value_type RampProcessor::advance()
{
    if (ramp.isDone(x))
    {
        if (!more_ramps)
            return x;

        updateRamp();
    }

    x = ramp.advance(x);
    return x;
}

//-----------------------------------------------------------------------------
RampProcessor::value_type RampProcessor::getValue() const
{
    return x;
}

//-----------------------------------------------------------------------------
void RampProcessor::updateRamp()
{
    current_segment++;
    initRamp(current_segment);
}

//-----------------------------------------------------------------------------
void RampProcessor::initRamp(int index)
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
        x    = val0;
        ramp = Ramp(val0, val0, 0);
        return;
    }

    int const duration = (offset1 - offset0);
    ramp               = Ramp(val0, val1, duration);
}

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha