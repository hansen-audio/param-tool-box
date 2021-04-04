// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/linear.h"
#include "ha/param_tool_box/convert/percent.h"

#include "gtest/gtest.h"

#include <vector>

namespace {

//-----------------------------------------------------------------------------
using linear_float = ha::ptb::convert::linear<float>;
static linear_float const linear_converter(0., 100.);

//-----------------------------------------------------------------------------
TEST(linear_test, convert_normalised_to_physical)
{
    EXPECT_FLOAT_EQ(linear_converter.to_physical(0.), 0.);
    EXPECT_FLOAT_EQ(linear_converter.to_physical(1.), 100.);
}

//-----------------------------------------------------------------------------
TEST(linear_test, convert_physical_to_string)
{
    EXPECT_EQ(linear_converter.to_string(0.), "0.00");
    EXPECT_EQ(linear_converter.to_string(10.), "10.00");
    EXPECT_EQ(linear_converter.to_string(99.f), "99.00");
}

//-----------------------------------------------------------------------------
TEST(linear_test, convert_string_to_physical)
{
    EXPECT_EQ(linear_converter.from_string("0"), 0.);
    EXPECT_EQ(linear_converter.from_string("10"), 10.);
    EXPECT_EQ(linear_converter.from_string("99.5"), 99.5);
}

//-----------------------------------------------------------------------------
TEST(linear_test, convert_to_string_with_precision)
{
    const auto precisionFunc = [](linear_float::value_type physical) { return 0; };
    EXPECT_EQ(linear_converter.to_string(0.5, precisionFunc), "1");
    EXPECT_EQ(linear_converter.to_string(50.3, precisionFunc), "50");
}

//-----------------------------------------------------------------------------
TEST(linear_test, convert_min_bigger_max)
{
    static linear_float const linear_converter(100., 0.);
    const auto precisionFunc = [](linear_float::value_type physical) { return 0; };
    EXPECT_EQ(linear_converter.to_string(50, precisionFunc), "50");
}

//-----------------------------------------------------------------------------
TEST(percent_test, convert_normalised_to_percent)
{
    ha::ptb::convert::percent<float> percent_converter;
    EXPECT_FLOAT_EQ(percent_converter.to_physical(0.), 0.);
    EXPECT_FLOAT_EQ(percent_converter.to_physical(1.), 100.);
}

//-----------------------------------------------------------------------------
} // namespace
