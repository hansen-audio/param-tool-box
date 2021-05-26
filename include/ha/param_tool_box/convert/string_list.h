// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/detail/lin_scale.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"
#include <functional>

namespace ha::ptb::convert {

//-----------------------------------------------------------------------------
/**
 * string_list
 */
template <typename RealType, typename StringListType>
class string_list
{
public:
    //-------------------------------------------------------------------------
    using value_type     = RealType const;
    using mut_value_type = RealType;
    using fn_precision   = std::function<i32(value_type)>;

    string_list(StringListType string_list);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    using scale_type = detail::lin_scale<mut_value_type>;
    typename scale_type::context cx;
    StringListType m_string_list;

    value_type round(value_type x) const;
};

//-----------------------------------------------------------------------------
//  string_list
//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
string_list<RealType, StringListType>::string_list(StringListType string_list)
: m_string_list(std::move(string_list))
{
    cx = scale_type::create(RealType(0.), RealType(m_string_list.size() - 1));
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
typename string_list<RealType, StringListType>::value_type
string_list<RealType, StringListType>::to_physical(value_type normalized) const
{
    value_type clamped = clamp(normalized, cx.norm_min, cx.norm_max);

    value_type rounded = scale_type::scale(cx, clamped);
    return round(rounded);
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
typename string_list<RealType, StringListType>::value_type
string_list<RealType, StringListType>::to_normalized(value_type physical) const
{
    value_type clamped = clamp(physical, cx.phys_min, cx.phys_max);

    return scale_type::scale_inverted(cx, clamped);
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
string_type string_list<RealType, StringListType>::to_string(value_type physical,
                                                             fn_precision const&) const
{
    i32 const index = static_cast<i32>(physical);

    string_type const tmp(m_string_list.at(index));
    return tmp;
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
typename string_list<RealType, StringListType>::value_type
string_list<RealType, StringListType>::from_string(string_type const& value_string) const
{
    // TODO
    return 0.;
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
typename string_list<RealType, StringListType>::value_type
string_list<RealType, StringListType>::round(value_type x) const
{
    return static_cast<value_type>(static_cast<i32>(x + RealType(0.5)));
}
//-----------------------------------------------------------------------------
} // namespace ha::ptb::convert