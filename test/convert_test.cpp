// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/dezibel.h"

#include "gtest/gtest.h"

#include <vector>

namespace {

//-----------------------------------------------------------------------------
using fDezibel = ha::ptb::convert::dezibel<float>;
static fDezibel const dB_converter(-96., 0.);

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_convertNormToDezibel)
{
    EXPECT_FLOAT_EQ(dB_converter.to_physical(1.f), 0.f);
    EXPECT_FLOAT_EQ(dB_converter.to_physical(0.f), -96.f);
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_convertPhysicaltoString)
{
    EXPECT_EQ(dB_converter.to_string(0.), "0.00");
    EXPECT_EQ(dB_converter.to_string(-6.), "-6.00");
    EXPECT_EQ(dB_converter.to_string(-95.f), "-95.00");
    EXPECT_EQ(dB_converter.to_string(-96.f), "-inf");
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_convertStringtoPhysical)
{
    EXPECT_EQ(dB_converter.from_string("0"), 0.);
    EXPECT_EQ(dB_converter.from_string("-6"), -6.);
    EXPECT_EQ(dB_converter.from_string("-95"), -95.);
    EXPECT_EQ(dB_converter.from_string("-inf"), -96);
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessorToStringPrecision)
{
    const auto precisionFunc = [](fDezibel::value_type physical) { return physical > -10 ? 2 : 1; };
    EXPECT_EQ(dB_converter.to_string(-6.54, precisionFunc), "-6.54");
    EXPECT_EQ(dB_converter.to_string(-23.45, precisionFunc), "-23.5");
}

//-----------------------------------------------------------------------------
} // namespace
