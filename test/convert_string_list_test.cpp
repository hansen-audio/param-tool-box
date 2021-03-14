// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/string_list.h"
#include "gtest/gtest.h"
#include <array>

namespace {
//-----------------------------------------------------------------------------
using float_t = float;

// clang-format off
using string_view_list = std::array<std::string_view, 9>;
static constexpr string_view_list delay_fade_note_length_strings = {
    "Instant",
    "1/16",
    "1/8",
    "1/4",
    "1/2",
    "1",
    "2",
    "3",
    "4"
};
// clang-format on
using string_list_float = ha::ptb::convert::string_list<float, string_view_list>;
static string_list_float const converter(delay_fade_note_length_strings);

//-----------------------------------------------------------------------------
TEST(string_list_test, convert_normalised_to_physical)
{
    EXPECT_FLOAT_EQ(converter.to_physical(0.), 0.);
    EXPECT_FLOAT_EQ(converter.to_physical(0.4), 3.);
    EXPECT_FLOAT_EQ(converter.to_physical(0.5), 4.);
    EXPECT_FLOAT_EQ(converter.to_physical(1.0), 8.);
}

//-----------------------------------------------------------------------------
TEST(string_list_test, convert_normalised_to_string_min)
{
    float_t const phys = converter.to_physical(0.);
    EXPECT_EQ(converter.to_string(phys), "Instant");
}

//-----------------------------------------------------------------------------
TEST(string_list_test, convert_normalised_to_string_max)
{
    float_t const phys = converter.to_physical(1.);
    EXPECT_EQ(converter.to_string(phys), "4");
}

//-----------------------------------------------------------------------------
TEST(string_list_test, convert_normalised_to_string_mid)
{
    float_t const phys = converter.to_physical(.5);
    EXPECT_EQ(converter.to_string(phys), "1/2");
}

//-----------------------------------------------------------------------------
} // namespace
