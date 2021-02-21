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
std::string to_string_with_precision(T const a_value, int const n = 6)
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
    using string_type                         = std::string const;
    using value_type                          = tRealType;
    using fn_precision                        = std::function<int(value_type)>;
    static value_type constexpr kReciprocal20 = value_type(1.) / value_type(20.);
    static int const kStandardPrecision       = 2;

    Dezibel(value_type min_dB, value_type max_dB)
    : min_dB(min_dB)
    , max_dB(max_dB)
    {
    }

    value_type toPhysical(value_type normalized) const
    {
        static value_type const kBase    = 10.;
        static value_type const kExp     = kReciprocal20 * min_dB;
        static value_type const kNormMin = pow(kBase, kExp);

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

    string_type toString(value_type physical, fn_precision const& precision_func = nullptr) const
    {
        int precision = kStandardPrecision;
        if (precision_func)
            precision = precision_func(physical);

        return physical <= min_dB ? "-inf" : to_string_with_precision(physical, precision);
    }

    value_type fromString(string_type const& value_string) const
    {
        // TODO: Make this more robust to non-digit inputs.
        value_type const value =
            value_string == "-inf" ? value_type(min_dB) : value_type(std::stod(value_string));
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