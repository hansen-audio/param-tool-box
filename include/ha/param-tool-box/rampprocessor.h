// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ramp.h"
#include <functional>

namespace HA {
namespace PTB {

//------------------------------------------------------------------------
// RampProcessor
//------------------------------------------------------------------------
class RampProcessor
{
public:
    //--------------------------------------------------------------------
    using ValueType     = Ramp::ValueType;
    using mut_ValueType = Ramp::mut_ValueType;

    using ParamValueQueue =
        std::function<bool(int /*index*/, int& /*offset*/, mut_ValueType& /*value*/)>;

    RampProcessor(ParamValueQueue queue, ValueType init);
    ValueType advance();
    ValueType getValue() const;

    //--------------------------------------------------------------------
private:
    void updateRamp();
    void initRamp(int index);

    Ramp ramp;
    ParamValueQueue queue = nullptr;
    int currSegment       = 0;
    bool moreRamps        = true;
    mut_ValueType x       = 0.f;
};

//-----------------------------------------------------------------------------
} // namespace PTB
} // namespace HA