// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <algorithm>
#include <functional>
#include <math.h>
#include <sstream>
#include <string>

namespace ha {
namespace ptb {
namespace convert {
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
class Dezibel final
{
public:
    //-------------------------------------------------------------------------
    using string_type                         = const std::string;
    using value_type                          = tRealType;
    using fn_precision                        = std::function<int(value_type)>;
    static constexpr value_type kReciprocal20 = value_type(1.) / value_type(20.);
    static const int kStandardPrecision       = 2;

    Dezibel(value_type min_dB, value_type max_dB)
    : min_dB(min_dB)
    , max_dB(max_dB)
    {
    }

    value_type toPhysical(value_type normalized) const
    {
        static constexpr value_type kBase = 10.;
        static const value_type kExp      = kReciprocal20 * min_dB;
        static const value_type kNormMin  = pow(kBase, kExp);

#if __cplusplus < 201700
        normalized = std::max(normalized, kNormMin);
        normalized = std::min(normalized, value_type(1));
#else
        normalized = std::clamp(normalized, kNormMin, value_type(1.));
#endif
        return value_type(20.) * log10(normalized);
    }

    value_type toNormalized(value_type physical) const
    {
#if __cplusplus < 201700
        physical = std::max(physical, min_dB);
        physical = std::min(physical, max_dB);
#else
        physical   = std::clamp(physical, min_dB, max_dB);
#endif
        return pow(value_type(10.), kReciprocal20 * physical);
    }

    string_type toString(value_type physical, const fn_precision& precision_func = nullptr) const
    {
        int precision = kStandardPrecision;
        if (precision_func)
            precision = precision_func(physical);

        return physical <= min_dB ? "-inf" : to_string_with_precision(physical, precision);
    }

    value_type fromString(const string_type& string) const
    {
        // TODO: Make this more robust to non-digit inputs.
        const value_type value =
            string == "-inf" ? value_type(min_dB) : value_type(std::stod(string));
        return value;
    }

    //-------------------------------------------------------------------------
private:
    value_type min_dB = -96.;
    value_type max_dB = 0.;
};

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha