// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/process/ramp.h"
#include <algorithm>
#include <math.h>

namespace ha {
namespace {

//------------------------------------------------------------------------
template <typename T>
T dezip(T x, T delta, T dst)
{
    const T kDiff = dst - x;
    if (kDiff > delta)
        x += delta;
    else if (kDiff < -delta)
        x -= delta;
    else
        x = dst;

    return x;
}

//------------------------------------------------------------------------
template <typename T>
T calcDelta(T cur, T dst, int n)
{
    return fabs(dst - cur) / static_cast<T>(n);
}

//------------------------------------------------------------------------
} // namespace

namespace ptb {
//-----------------------------------------------------------------------------
// Ramp
//-----------------------------------------------------------------------------
Ramp::Ramp(value_type src, value_type dst, int numSamples)
: src(src)
, dst(dst)
, delta(calcDelta(src, dst, std::max(numSamples, 1)))
{
    // _numSamples > 0 to prevent division by zero.
}

//-----------------------------------------------------------------------------
Ramp::value_type Ramp::advance(value_type x)
{
    return dezip(x, delta, dst);
}

//-----------------------------------------------------------------------------
bool Ramp::isDone(value_type x) const
{
    return x == dst;
}

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha