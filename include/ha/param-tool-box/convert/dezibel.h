// Copyright(c) 2021 Hansen Audio.

#pragma once

#include <algorithm>
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
template <typename RealType, int tPrecision>
class Dezibel
{
public:
    //-------------------------------------------------------------------------
    static constexpr RealType kMin     = -96.;
    static constexpr RealType kMax     = 0.;
    static constexpr RealType kBase    = 10.;
    static constexpr RealType kExp     = (RealType(1.) / RealType(20.)) * kMin;
    static constexpr RealType kNormMin = pow(kBase, kExp);

    using StringType = std::string;

    Dezibel() {}

    RealType toPhysical(RealType normalized) const
    {
#if __cplusplus < 201700
        normalized = std::max(normalized, kNormMin);
        normalized = std::min(normalized, RealType(1));
#else
        normalized = std::clamp(normalized, kNormMin, RealType(1));
#endif
        return RealType(20.) * log(normalized) / log(RealType(10.));
    }

    RealType toNormalized(RealType physical) const
    {
#if __cplusplus < 201700
        physical = std::max(physical, kMin);
        physical = std::min(physical, kMax);
#else
        physical   = std::clamp(physical, kMin, kMax);
#endif
        return pow(RealType(10.), RealType(1.) / RealType(20.) * physical);
    }

    StringType toString(RealType physical) const
    {
        return physical <= kMin ? "-oo" : to_string_with_precision(physical, tPrecision);
    }

    RealType fromString(const StringType& string) const
    {
        auto value = string == "-oo" ? RealType(kMin) : std::stof(string);
        return value;
    }

    //-------------------------------------------------------------------------
private:
};

//-----------------------------------------------------------------------------
} // namespace Convert
} // namespace PTB
} // namespace HA