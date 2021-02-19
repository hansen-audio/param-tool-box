// Copyright(c) 2021 Hansen Audio.

#include "ha/ptb/paramrampprocessor.h"
#include <algorithm>

namespace HA {
namespace PTB {

//------------------------------------------------------------------------
// ParamRampProcessor
//------------------------------------------------------------------------
ParamRampProcessor::ParamRampProcessor(ParamValueQueue queue, ValueType init)
: queue(queue)
, ramp({init, init, 0})
, x(init)
{
    initRamp(0);
}

//-----------------------------------------------------------------------------
ParamRampProcessor::ValueType ParamRampProcessor::advance()
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
ParamRampProcessor::ValueType ParamRampProcessor::getValue() const
{
    return x;
}

//-----------------------------------------------------------------------------
void ParamRampProcessor::updateRamp()
{
    currSegment++;
    initRamp(currSegment);
}

//-----------------------------------------------------------------------------
void ParamRampProcessor::initRamp(int index)
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
        ramp = ParamRamp(val0, val0, 0);
        return;
    }

    const int duration = (offset1 - offset0);
    ramp               = ParamRamp(val0, val1, duration);
}

//-----------------------------------------------------------------------------
} // namespace PTB
} // namespace HA