// Copyright(c) 2021 Hansen Audio.

#pragma once

namespace HA {
namespace PTB {

//------------------------------------------------------------------------
//  Ramp
//------------------------------------------------------------------------
class Ramp final
{
public:
    //------------------------------------------------------------------------
    using ValueType     = const float;
    using mut_ValueType = float;

    Ramp(ValueType src, ValueType dst, int _numSamples);
    ValueType advance(ValueType x);
    bool isDone(ValueType x) const;

    //------------------------------------------------------------------------
private:
    mut_ValueType src   = 0.f;
    mut_ValueType dst   = 0.f;
    mut_ValueType delta = 0.1f;
};

//-----------------------------------------------------------------------------
} // namespace PTB
} // namespace HA