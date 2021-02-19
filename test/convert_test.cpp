// Copyright(c) 2021 Hansen Audio.

#include "ha/param-tool-box/convert/dezibel.h"

#include "gtest/gtest.h"

#include <vector>

using namespace HA::PTB;

namespace {

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_convertNormToDezibel)
{
    constexpr int kPrecision = 2;

    Convert::Dezibel<float, kPrecision> dB_converter;
    EXPECT_FLOAT_EQ(dB_converter.toPhysical(1.f), 0.f);
    EXPECT_FLOAT_EQ(dB_converter.toPhysical(0.f), -96.f);
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_convertPhysicalToString)
{
    constexpr int kPrecision = 2;

    Convert::Dezibel<float, kPrecision> dB_converter;
    EXPECT_EQ(dB_converter.toString(0.), "0.00");
    EXPECT_EQ(dB_converter.toString(-6.), "-6.00");
    EXPECT_EQ(dB_converter.toString(-95.f), "-95.00");
    EXPECT_EQ(dB_converter.toString(-96.f), "-oo");
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_convertStringToPhysical)
{
    constexpr int kPrecision = 2;

    Convert::Dezibel<float, kPrecision> dB_converter;
    EXPECT_EQ(dB_converter.fromString("0"), 0.);
    EXPECT_EQ(dB_converter.fromString("-6"), -6.);
    EXPECT_EQ(dB_converter.fromString("-95"), -95.);
    EXPECT_EQ(dB_converter.fromString("-oo"), -96);
}

//-----------------------------------------------------------------------------
} // namespace
