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
constexpr T const& clamp(T const& v, T const& lo, T const& hi)
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
// dezibel
//-----------------------------------------------------------------------------
template <typename RealType>
class dezibel final
{
public:
    //-------------------------------------------------------------------------
    using string_type                          = std::string const;
    using value_type                           = RealType;
    using fn_precision                         = std::function<int(value_type)>;
    static value_type constexpr creciprocal_20 = value_type(1.) / value_type(20.);
    static int const cstandard_precision       = 2;

    dezibel(value_type lo, value_type hi)
    : lo(lo)
    , hi(hi)
    {
    }

    value_type to_physical(value_type normalized) const
    {
        static value_type const cbase     = value_type(10.);
        static value_type const cexp      = creciprocal_20 * lo;
        static value_type const cnorm_min = pow(cbase, cexp);

        normalized = clamp(normalized, cnorm_min, value_type(1.));

        return value_type(20.) * log10(normalized);
    }

    value_type to_normalized(value_type physical) const
    {
        physical = clamp(physical, lo, hi);

        return pow(value_type(10.), creciprocal_20 * physical);
    }

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const
    {
        value_type const tmp_physical = clamp(physical, lo, hi);
        int const precision = precision_func ? precision_func(tmp_physical) : cstandard_precision;

        return tmp_physical <= lo ? "-inf" : to_string_with_precision(tmp_physical, precision);
    }

    value_type from_string(string_type const& value_string) const
    {
        // TODO: Make this more robust to non-digit inputs.
        value_type const value =
            value_string == "-inf" ? value_type(lo) : value_type(std::stod(value_string));

        return clamp(value, lo, hi);
    }

    //-------------------------------------------------------------------------
private:
    value_type lo = -96.;
    value_type hi = 0.;
};

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha