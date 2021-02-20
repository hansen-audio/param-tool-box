// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <algorithm>
#include <functional>
#include <math.h>
#include <sstream>
#include <string>

namespace HA {
namespace PTB {
namespace Convert {
namespace {

//-----------------------------------------------------------------------------
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

//-----------------------------------------------------------------------------
} // namespace

//-----------------------------------------------------------------------------
// Dezibel
//-----------------------------------------------------------------------------
template <typename tRealType>
class Dezibel
{
public:
    //-------------------------------------------------------------------------
    using StringType    = const std::string;
    using value_type    = tRealType;
    using PrecisionFunc = std::function<int(value_type)>;

    static const int kStandardPrecision = 2;

    Dezibel(value_type min, value_type max)
    : kMin(min)
    , kMax(max)
    {
    }

    value_type toPhysical(value_type normalized) const
    {
        static constexpr value_type kBase = 10.;
        static const value_type kExp      = (value_type(1.) / value_type(20.)) * kMin;
        static const value_type kNormMin  = pow(kBase, kExp);

#if __cplusplus < 201700
        normalized = std::max(normalized, kNormMin);
        normalized = std::min(normalized, value_type(1));
#else
        normalized = std::clamp(normalized, kNormMin, value_type(1.));
#endif
        return value_type(20.) * log(normalized) / log(value_type(10.));
    }

    value_type toNormalized(value_type physical) const
    {
#if __cplusplus < 201700
        physical = std::max(physical, kMin);
        physical = std::min(physical, kMax);
#else
        physical   = std::clamp(physical, kMin, kMax);
#endif
        return pow(value_type(10.), value_type(1.) / value_type(20.) * physical);
    }

    StringType toString(value_type physical, const PrecisionFunc& func = nullptr) const
    {
        int precision = kStandardPrecision;
        if (func)
            precision = func(physical);

        return physical <= kMin ? "-inf" : to_string_with_precision(physical, precision);
    }

    value_type fromString(const StringType& string) const
    {
        // TODO: Make this more robust to non-digit inputs.
        const value_type value =
            string == "-inf" ? value_type(kMin) : value_type(std::stod(string));
        return value;
    }

    //-------------------------------------------------------------------------
private:
    value_type kMin = -96.;
    value_type kMax = 0.;
};

//-----------------------------------------------------------------------------
} // namespace Convert
} // namespace PTB
} // namespace HA