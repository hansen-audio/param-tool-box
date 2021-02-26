// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <cstdint>

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
//  ramp
//------------------------------------------------------------------------
class ramp final
{
public:
    //------------------------------------------------------------------------
    using value_type     = const float;
    using mut_value_type = float;
    using i32            = std::int32_t;

    ramp(value_type src, value_type dst, i32 _num_samples);

    value_type advance(value_type x);
    bool is_done(value_type x) const;

    //------------------------------------------------------------------------
private:
    mut_value_type src   = 0.f;
    mut_value_type dst   = 0.f;
    mut_value_type delta = 0.1f;
};

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha