// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "paramramp.h"
#include <functional>

namespace HA {
namespace PTB {

//------------------------------------------------------------------------
// ParamRampProcessor
//------------------------------------------------------------------------
class ParamRampProcessor
{
public:
    //--------------------------------------------------------------------
    using ValueType     = ParamRamp::ValueType;
    using mut_ValueType = ParamRamp::mut_ValueType;

    using ParamValueQueue =
        std::function<bool(int /*index*/, int& /*offset*/, mut_ValueType& /*value*/)>;

    ParamRampProcessor(ParamValueQueue queue, ValueType init);
    ValueType advance();
    ValueType getValue() const;

    //--------------------------------------------------------------------
private:
    void updateRamp();
    void initRamp(int index);

    ParamRamp ramp;
    ParamValueQueue queue = nullptr;
    int currSegment       = 0;
    bool moreRamps        = true;
    mut_ValueType x       = 0.f;
};

//-----------------------------------------------------------------------------
} // namespace PTB
} // namespace HA