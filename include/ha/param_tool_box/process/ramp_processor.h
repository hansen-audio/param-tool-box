// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/dezibel.h"
#include "ramp.h"
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
    using fn_value_queue =
        std::function<bool(int /*index*/, int& /*offset*/, mut_value_type& /*value*/)>;

    ramp_processor(fn_value_queue queue, value_type init);

    value_type advance();
    value_type get_value() const;

    //--------------------------------------------------------------------
private:
    void update_ramp();
    void init_ramp(int index);

    ramp current_ramp;
    fn_value_queue queue_func = nullptr;
    int current_segment       = 0;
    bool more_ramps           = true;
    mut_value_type x          = 0.f;
};

//-----------------------------------------------------------------------------
} // namespace ptb
} // namespace ha