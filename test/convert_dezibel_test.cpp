// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/dezibel.h"

#include "gtest/gtest.h"

#include <vector>

namespace {

//-----------------------------------------------------------------------------
using fDezibel = ha::ptb::convert::dezibel<float>;
static fDezibel const dB_converter(-96., 0.);

//-----------------------------------------------------------------------------
TEST(dezibel_test, convert_normalised_to_physical)
{
    EXPECT_FLOAT_EQ(dB_converter.to_physical(1.f), 0.f);
    EXPECT_FLOAT_EQ(dB_converter.to_physical(0.f), -96.f);
}

//-----------------------------------------------------------------------------
TEST(dezibel_test, convert_physical_to_string)
{
    EXPECT_EQ(dB_converter.to_string(0.), "0.00");
    EXPECT_EQ(dB_converter.to_string(-6.), "-6.00");
    EXPECT_EQ(dB_converter.to_string(-95.f), "-95.00");
    EXPECT_EQ(dB_converter.to_string(-96.f), "-inf");
}

//-----------------------------------------------------------------------------
TEST(dezibel_test, convert_string_to_physical)
{
    EXPECT_EQ(dB_converter.from_string("0"), 0.);
    EXPECT_EQ(dB_converter.from_string("-6"), -6.);
    EXPECT_EQ(dB_converter.from_string("-95"), -95.);
    EXPECT_EQ(dB_converter.from_string("-inf"), -96);
}

//-----------------------------------------------------------------------------
TEST(dezibel_test, convert_to_string_with_precision)
{
    const auto precisionFunc = [](fDezibel::value_type physical) { return physical > -10 ? 2 : 1; };
    EXPECT_EQ(dB_converter.to_string(-6.54, precisionFunc), "-6.54");
    EXPECT_EQ(dB_converter.to_string(-23.45, precisionFunc), "-23.5");
}

//-----------------------------------------------------------------------------
TEST(dezibel_test, convert_physical_to_normalised)
{
    EXPECT_FLOAT_EQ(dB_converter.to_normalized(0.f), 1.f);
    // EXPECT_FLOAT_EQ(dB_converter.to_normalized(-96.f), 0.000015849f); // Is a bit too inaccurate.
    EXPECT_NEAR(dB_converter.to_normalized(-96.f), 0.000015849f, 0.000001);
}

//-----------------------------------------------------------------------------
} // namespace
