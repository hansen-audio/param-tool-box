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
T calc_delta(T cur, T dst, int n)
{
    return fabs(dst - cur) / static_cast<T>(n);
}

//------------------------------------------------------------------------
} // namespace

namespace ptb {
//-----------------------------------------------------------------------------
// ramp
//-----------------------------------------------------------------------------
ramp::ramp(value_type src, value_type dst, int num_samples)
: src(src)
, dst(dst)
, delta(calc_delta(src, dst, std::max(num_samples, 1)))
{
    // num_samples > 0 to prevent division by zero.
}

//-----------------------------------------------------------------------------
ramp::value_type ramp::advance(value_type x)
{
    return dezip(x, delta, dst);
}

//-----------------------------------------------------------------------------
bool ramp::is_done(value_type x) const
{
    return x == dst;
}

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha