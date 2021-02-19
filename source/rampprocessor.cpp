// Copyright(c) 2021 Hansen Audio.

#include "ha/param-tool-box/process/rampprocessor.h"
#include <algorithm>

namespace HA {
namespace PTB {

//------------------------------------------------------------------------
// RampProcessor
//------------------------------------------------------------------------
RampProcessor::RampProcessor(ParamValueQueue queue, ValueType init)
: queue(queue)
, ramp({init, init, 0})
, x(init)
{
    initRamp(0);
}

//-----------------------------------------------------------------------------
RampProcessor::ValueType RampProcessor::advance()
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
RampProcessor::ValueType RampProcessor::getValue() const
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
    int offset0        = 0;
    mut_ValueType val0 = 0.;
    moreRamps          = queue(index++, offset0, val0);
    if (!moreRamps)
        return;

    int offset1        = 0;
    mut_ValueType val1 = 0.;
    moreRamps          = queue(index, offset1, val1);
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
} // namespace PTB
} // namespace HA