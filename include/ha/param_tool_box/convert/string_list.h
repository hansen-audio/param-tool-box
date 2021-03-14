// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/param_tool_box/convert/lin_scale.h"
#include "ha/param_tool_box/core/clamp.h"
#include "ha/param_tool_box/core/to_string.h"
#include "ha/param_tool_box/core/types.h"

#include <algorithm>
#include <functional>
#include <math.h>

namespace ha {
namespace ptb {
namespace convert {

//-----------------------------------------------------------------------------
/*
 * string_list
 */
template <typename RealType, typename StringListType>
class string_list
{
public:
    //-------------------------------------------------------------------------
    using value_type   = RealType;
    using fn_precision = std::function<i32(value_type)>;

    string_list(StringListType string_list);

    value_type to_physical(value_type normalized) const;

    value_type to_normalized(value_type physical) const;

    string_type to_string(value_type physical, fn_precision const& precision_func = nullptr) const;

    value_type from_string(string_type const& value_string) const;

    //-------------------------------------------------------------------------
private:
    value_type round(value_type x) const;
    typename detail::lin_scale<value_type>::context_type context;
    StringListType m_string_list;
};

//-----------------------------------------------------------------------------
//  string_list
//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
string_list<RealType, StringListType>::string_list(StringListType string_list)
: m_string_list(std::move(string_list))
{
    context = detail::lin_scale<value_type>::create(0, m_string_list.size() - 1);
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
typename string_list<RealType, StringListType>::value_type
string_list<RealType, StringListType>::to_physical(value_type normalized) const
{
    normalized = clamp(normalized, context.norm_min, context.norm_max);

    value_type rounded = detail::lin_scale<value_type>::scale(normalized, context);
    return round(rounded);
}

//-----------------------------------------------------------------------------
template <typename RealType, typename StringListType>
typename string_list<RealType, StringListType>::value_type
string_list<RealType, StringListType>::to_normalized(value_type physical) const
{
    physical = clamp(physical, context.phys_min, context.phys_max);

    return detail::lin_scale<value_type>::scale_inverted(physical, context);
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
} // namespace convert
} // namespace ptb
} // namespace ha