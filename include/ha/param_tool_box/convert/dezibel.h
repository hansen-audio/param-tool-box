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
template <class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
#if __cplusplus < 201700
    T const tmp_v = std::max(v, lo);
    return std::min(tmp_v, hi);
#else
    return std::clamp(v, lo, hi);
#endif
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

        normalized = std::max(normalized, kNormMin);
        normalized = std::min(normalized, value_type(1));
        normalized = clamp(normalized, kNormMin, value_type(1.));

        return value_type(20.) * log10(normalized);
    }

    value_type toNormalized(value_type physical) const
    {
        physical = clamp(physical, min_dB, max_dB);

        return pow(value_type(10.), kReciprocal20 * physical);
    }

    string_type toString(value_type physical, fn_precision const& precision_func = nullptr) const
    {
        value_type const tmp_physical = clamp(physical, min_dB, max_dB);
        int const precision = precision_func ? precision_func(tmp_physical) : kStandardPrecision;

        return tmp_physical <= min_dB ? "-inf" : to_string_with_precision(tmp_physical, precision);
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