// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/dezibel.h"
#include "ramp.h"
#include <cstdint>
#include <functional>

namespace ha {
namespace ptb {

//------------------------------------------------------------------------
// ramp_processor
//------------------------------------------------------------------------
class ramp_processor
{
public:
    //--------------------------------------------------------------------
    using value_type     = ramp::value_type;
    using mut_value_type = ramp::mut_value_type;
    using i32            = std::int32_t;
    using fn_value_queue =
        std::function<bool(i32 /*index*/, i32& /*offset*/, mut_value_type& /*value*/)>;

    ramp_processor(fn_value_queue queue, value_type init);

    value_type advance();
    value_type get_value() const;

    //--------------------------------------------------------------------
private:
    void update_ramp();
    void init_ramp(i32 index);

    ramp current_ramp;
    fn_value_queue queue_func = nullptr;
    i32 current_segment       = 0;
    bool more_ramps           = true;
    mut_value_type x          = 0.f;
};

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha