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
    using RealType      = tRealType;
    using PrecisionFunc = std::function<int(RealType)>;

    static const int kStandardPrecision = 2;

    Dezibel(RealType min, RealType max)
    : kMin(min)
    , kMax(max)
    {
    }

    RealType toPhysical(RealType normalized) const
    {
        static constexpr RealType kBase = 10.;
        static const RealType kExp      = (RealType(1.) / RealType(20.)) * kMin;
        static const RealType kNormMin  = pow(kBase, kExp);

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

    StringType toString(RealType physical, const PrecisionFunc& func = nullptr) const
    {
        int precision = kStandardPrecision;
        if (func)
            precision = func(physical);

        return physical <= kMin ? "-inf" : to_string_with_precision(physical, precision);
    }

    RealType fromString(const StringType& string) const
    {
        auto value = string == "-inf" ? RealType(kMin) : std::stof(string);
        return value;
    }

    //-------------------------------------------------------------------------
private:
    RealType kMin = -96.;
    RealType kMax = 0.;
};

//-----------------------------------------------------------------------------
} // namespace Convert
} // namespace PTB
} // namespace HA