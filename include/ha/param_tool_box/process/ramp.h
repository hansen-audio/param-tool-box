// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"

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

    ramp(value_type src, value_type dst, i32 _num_samples);

    value_type advance(value_type x);
    bool is_done(value_type x) const;

    //------------------------------------------------------------------------
private:
    mut_value_type src   = value_type(0.0);
    mut_value_type dst   = value_type(0.0);
    mut_value_type delta = value_type(0.1);
};

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha