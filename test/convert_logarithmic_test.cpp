// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/logarithmic.h"

#include "gtest/gtest.h"

#include <vector>

namespace {

//-----------------------------------------------------------------------------
using converter_type = ha::ptb::convert::logarithmic<float>;

//-----------------------------------------------------------------------------
TEST(logarithmic_test, convert_normalised_to_physical)
{
    static converter_type const converter(0.01f, 30.f, 1.f);
    EXPECT_FLOAT_EQ(converter.to_physical(1.f), 30.f);
    EXPECT_FLOAT_EQ(converter.to_physical(0.f), 0.01f);
    EXPECT_FLOAT_EQ(converter.to_physical(0.5f), 1.f);
}

//-----------------------------------------------------------------------------
TEST(logarithmic_test, convert_physical_to_string)
{
    static converter_type const converter(0.001f, 4.f, 0.25f);
    EXPECT_FLOAT_EQ(converter.to_physical(1.f), 4.f);
    EXPECT_FLOAT_EQ(converter.to_physical(0.f), 0.001f);
    EXPECT_FLOAT_EQ(converter.to_physical(0.5f), 0.25f);
}

//-----------------------------------------------------------------------------
TEST(logarithmic_test, convert_to_physical_negative)
{
    static converter_type const converter(-96.f, 6.f, 0.f);
    EXPECT_FLOAT_EQ(converter.to_physical(1.f), 6.f);
    EXPECT_FLOAT_EQ(converter.to_physical(0.f), -96.f);
    EXPECT_FLOAT_EQ(converter.to_physical(0.5f), 0.f);
}

//-----------------------------------------------------------------------------
} // namespace
