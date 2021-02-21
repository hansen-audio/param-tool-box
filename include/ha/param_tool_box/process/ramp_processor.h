// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/dezibel.h"
#include "ramp.h"
#include <functional>

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
// RampProcessor
//------------------------------------------------------------------------
class RampProcessor
{
public:
    //--------------------------------------------------------------------
    using value_type     = Ramp::value_type;
    using mut_value_type = Ramp::mut_value_type;

    using FuncParamValueQueue =
        std::function<bool(int /*index*/, int& /*offset*/, mut_value_type& /*value*/)>;

    RampProcessor(FuncParamValueQueue queue, value_type init);
    value_type advance();
    value_type getValue() const;

    //--------------------------------------------------------------------
private:
    void updateRamp();
    void initRamp(int index);

    Ramp ramp;
    FuncParamValueQueue queueFunc = nullptr;
    int currSegment               = 0;
    bool moreRamps                = true;
    mut_value_type x              = 0.f;
};

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha