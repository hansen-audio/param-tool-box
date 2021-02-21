// Copyright(c) 2021 Hansen Audio.

#pragma once

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
//  Ramp
//------------------------------------------------------------------------
class Ramp final
{
public:
    //------------------------------------------------------------------------
    using value_type     = const float;
    using mut_value_type = float;

    Ramp(value_type src, value_type dst, int _num_samples);
    value_type advance(value_type x);
    bool isDone(value_type x) const;

    //------------------------------------------------------------------------
private:
    mut_value_type src   = 0.f;
    mut_value_type dst   = 0.f;
    mut_value_type delta = 0.1f;
};

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha