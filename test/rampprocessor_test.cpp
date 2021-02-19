// Copyright(c) 2021 Hansen Audio.

#include "ha/param-tool-box/rampprocessor.h"

#include "gtest/gtest.h"

#include <vector>

using namespace HA::PTB;

using ValueType     = RampProcessor::ValueType;
using mut_ValueType = RampProcessor::mut_ValueType;

struct ParamData
{
    int offset    = 0;
    ValueType val = 0.f;
};

using ParamValueQueue = std::vector<ParamData>;

namespace {
//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_invalidQueue)
{
    constexpr float kInitVal = 0.5f;
    int counter              = 0;
    auto cb                  = [&counter](int index, int& offset, mut_ValueType& value) -> bool {
        counter++;
        return false;
    };

    RampProcessor proc(cb, kInitVal);
    EXPECT_FLOAT_EQ(proc.getValue(), kInitVal);
    EXPECT_FLOAT_EQ(proc.advance(), kInitVal);
    EXPECT_FLOAT_EQ(proc.advance(), kInitVal);
    EXPECT_FLOAT_EQ(proc.advance(), kInitVal);
    EXPECT_EQ(counter, 1);
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_noRampValueFromGUIEditor)
{
    static const ParamValueQueue kValueQueue = {{0, 0.75f}};
    constexpr float kInitVal                 = 0.5f;
    int counter                              = 0;
    auto cb = [&counter](int index, int& offset, mut_ValueType& value) -> bool {
        ++counter;

        if (index < kValueQueue.size())
        {
            const ParamData& data = kValueQueue.at(index);
            offset                = data.offset;
            value                 = data.val;
            return true;
        }
        return false;
    };

    RampProcessor proc(cb, kInitVal);
    EXPECT_FLOAT_EQ(proc.getValue(), 0.75f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.75f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.75f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.75f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.75f);
    EXPECT_EQ(counter, 2);
}

//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_oneRamp)
{
    constexpr float kInitVal                 = 0.6f;
    static const ParamValueQueue kValueQueue = {{0, kInitVal}, {4, 1.0f}};
    int counter                              = 0;
    auto cb = [&counter](int index, int& offset, mut_ValueType& value) -> bool {
        ++counter;

        if (index < kValueQueue.size())
        {
            const ParamData& data = kValueQueue.at(index);
            offset                = data.offset;
            value                 = data.val;
            return true;
        }
        return false;
    };

    RampProcessor proc(cb, kInitVal);
    EXPECT_FLOAT_EQ(proc.getValue(), kInitVal);
    EXPECT_FLOAT_EQ(proc.advance(), 0.7f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.8f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.9f);
    EXPECT_FLOAT_EQ(proc.advance(), 1.0f);

    EXPECT_EQ(counter, 2);
}
//-----------------------------------------------------------------------------
TEST(ParamToolBoxTest, testRampProcessor_twoRamps)
{
    constexpr float kInitVal                 = 0.6f;
    static const ParamValueQueue kValueQueue = {{0, kInitVal}, {4, 1.0f}, {9, 0.5f}};
    int counter                              = 0;
    auto cb = [&counter](int index, int& offset, mut_ValueType& value) -> bool {
        ++counter;

        if (index < kValueQueue.size())
        {
            const ParamData& data = kValueQueue.at(index);
            offset                = data.offset;
            value                 = data.val;
            return true;
        }
        return false;
    };

    RampProcessor proc(cb, kInitVal);
    EXPECT_FLOAT_EQ(proc.getValue(), kInitVal);
    EXPECT_FLOAT_EQ(proc.advance(), 0.7f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.8f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.9f);
    EXPECT_FLOAT_EQ(proc.advance(), 1.0f);

    EXPECT_FLOAT_EQ(proc.getValue(), 1.0f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.9f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.8f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.7f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.6f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.5f);

    EXPECT_FLOAT_EQ(proc.advance(), 0.5f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.5f);
    EXPECT_FLOAT_EQ(proc.advance(), 0.5f);

    EXPECT_EQ(counter, 6);
}

//-----------------------------------------------------------------------------
} // namespace
