// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/core/types.h"
#include <algorithm>
#include <functional>
#include <math.h>
#include <sstream>

namespace ha {
namespace ptb {
namespace convert {
namespace {

//-----------------------------------------------------------------------------
template <typename T>
std::string to_string_with_precision(T const a_value, i32 const n = 6)
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
    using value_type                          = RealType;
    using fn_precision                        = std::function<i32(value_type)>;
    static value_type constexpr RECIPROCAL_20 = value_type(1.) / value_type(20.);
    static i32 const STANDARD_PRECISION       = 2;

    dezibel(value_type lo, value_type hi);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    value_type lo = -96.;
    value_type hi = 0.;
};

//-----------------------------------------------------------------------------
//  dezibel
//-----------------------------------------------------------------------------
template <typename RealType>
dezibel<RealType>::dezibel(value_type lo, value_type hi)
: lo(lo)
, hi(hi)
{
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type dezibel<RealType>::to_physical(value_type normalized) const
{
    constexpr value_type BASE              = value_type(10.);
    constexpr value_type NOMRALIZED_MAX    = value_type(1.);
    static value_type const EXPONENT       = RECIPROCAL_20 * lo;
    static value_type const NOMRALIZED_MIN = pow(BASE, EXPONENT);

    normalized = clamp(normalized, NOMRALIZED_MIN, NOMRALIZED_MAX);

    return value_type(20.) * log10(normalized);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type dezibel<RealType>::to_normalized(value_type physical) const
{
    physical = clamp(physical, lo, hi);

    return pow(value_type(10.), RECIPROCAL_20 * physical);
}

//-----------------------------------------------------------------------------
template <typename RealType>
string_type dezibel<RealType>::to_string(value_type physical,
                                         fn_precision const& precision_func) const
{
    value_type const tmp_physical = clamp(physical, lo, hi);
    i32 const precision = precision_func ? precision_func(tmp_physical) : STANDARD_PRECISION;

    return tmp_physical <= lo ? "-inf" : to_string_with_precision(tmp_physical, precision);
}

//-----------------------------------------------------------------------------
template <typename RealType>
typename dezibel<RealType>::value_type
dezibel<RealType>::from_string(string_type const& value_string) const
{
    // TODO: Make this more robust to non-digit inputs.
    value_type const value =
        value_string == "-inf" ? value_type(lo) : value_type(std::stod(value_string));

    return clamp(value, lo, hi);
}

//-----------------------------------------------------------------------------
} // namespace convert
} // namespace ptb
} // namespace ha