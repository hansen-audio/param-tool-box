// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/detail/log_scale.h"
#include "gtest/gtest.h"
#include <vector>

namespace {

//-----------------------------------------------------------------------------
using float_t         = float;
using log_scale_float = ha::ptb::convert::detail::log_scale<float_t>;

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_50)
{
    constexpr float_t expected = 50.;

    auto context   = log_scale_float::create(0., 100., expected);
    float_t result = log_scale_float::scale(0.5, context);

    EXPECT_FLOAT_EQ(result, expected);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_25)
{
    constexpr float_t expected = 25.;

    auto context   = log_scale_float::create(0., 100., expected);
    float_t result = log_scale_float::scale(0.5, context);

    EXPECT_FLOAT_EQ(result, expected);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_75)
{
    constexpr float_t expected = 75.;

    auto context   = log_scale_float::create(0., 100., expected);
    float_t result = log_scale_float::scale(0.5, context);

    EXPECT_FLOAT_EQ(result, expected);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_negative)
{
    constexpr float_t expected = 3.;

    auto context   = log_scale_float::create(-96., 6., expected);
    float_t result = log_scale_float::scale(0.5, context);

    EXPECT_FLOAT_EQ(result, expected);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_negative_min)
{
    constexpr float_t expected = -96.;

    auto context   = log_scale_float::create(expected, 6., 0.);
    float_t result = log_scale_float::scale(0., context);

    EXPECT_FLOAT_EQ(result, expected);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_negative_max)
{
    constexpr float_t expected = 6.;

    auto context   = log_scale_float::create(-96., expected, 0.);
    float_t result = log_scale_float::scale(1., context);

    EXPECT_FLOAT_EQ(result, expected);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_lfo)
{
    auto context = log_scale_float::create(0.01f, 30.f, 1.f);

    EXPECT_FLOAT_EQ(log_scale_float::scale(1., context), 30.f);
    EXPECT_FLOAT_EQ(log_scale_float::scale(0., context), 0.01f);
    EXPECT_FLOAT_EQ(log_scale_float::scale(0.5, context), 1.f);
}

//-----------------------------------------------------------------------------
TEST(log_scale_test, scale_normalised_to_physical_lfo_max_min)
{
    auto context = log_scale_float::create(30.f, 0.01f, 1.f);

    // EXPECT_FLOAT_EQ(log_scale_float::scale(1., context), 0.01f); // Is a bit too inaccurate.
    EXPECT_NEAR(log_scale_float::scale(1., context), 0.01f, 0.000001);
    EXPECT_FLOAT_EQ(log_scale_float::scale(0., context), 30.f);
    EXPECT_FLOAT_EQ(log_scale_float::scale(0.5, context), 1.f);
}
//-----------------------------------------------------------------------------
} // namespace
