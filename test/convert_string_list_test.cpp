// Copyright(c) 2021 Hansen Audio.

#include "ha/param_tool_box/convert/string_list.h"
#include "gtest/gtest.h"
#include <array>

namespace {

//-----------------------------------------------------------------------------
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
} // namespace
