// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/process/ramp_processor.h"
#include <algorithm>

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
// RampProcessor
//------------------------------------------------------------------------
RampProcessor::RampProcessor(FuncParamValueQueue queueFunc, value_type init)
: queueFunc(std::move(queueFunc))
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
        if (!moreRamps)
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
    currSegment++;
    initRamp(currSegment);
}

//-----------------------------------------------------------------------------
void RampProcessor::initRamp(int index)
{
    int offset0         = 0;
    mut_value_type val0 = 0.;
    moreRamps           = queueFunc ? queueFunc(index++, offset0, val0) : false;
    if (!moreRamps)
        return;

    int offset1         = 0;
    mut_value_type val1 = 0.;
    moreRamps           = queueFunc(index, offset1, val1);
    if (!moreRamps)
    {
        x    = val0;
        ramp = Ramp(val0, val0, 0);
        return;
    }

    const int duration = (offset1 - offset0);
    ramp               = Ramp(val0, val1, duration);
}

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha