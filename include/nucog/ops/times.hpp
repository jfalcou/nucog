//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_TIMES_HPP_INCLUDED
#define NUCOG_OPS_TIMES_HPP_INCLUDED

#include <nucog/detail/supports_overload.hpp>
#include <nucog/expr/as_expr.hpp>
#include <nucog/expr/match.hpp>
#include <nucog/expr/child.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/literal.hpp>

namespace nucog::tags
{
  struct times_ : tag<times_>
  {};
}

namespace nucog
{
  template<typename XLHS, typename XRHS, typename = supports_overload<XLHS,XRHS>>
  constexpr auto operator*( XLHS&& lhs, XRHS&& rhs ) noexcept
  {
    return make(tags::times_{}, as_expr(std::forward<XLHS>(lhs)), as_expr(std::forward<XRHS>(rhs)));
  }
}

// -------------------------------------------------------------------------------------------------
// Optimization
namespace nucog::tags
{
  template<typename XLHS, typename XRHS>
  constexpr auto make( times_ const&, expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    using namespace literal;

    if constexpr( XLHS::is_placeholder() || XRHS::is_placeholder() )
    {
      return node<tags::times_,XLHS, XRHS>{lhs.self(), rhs.self()};
    }
    else
    {
           if constexpr( NUCOG_MATCH(lhs,0_c) || NUCOG_MATCH(rhs,0_c) ) return 0_c;
      else if constexpr( NUCOG_MATCH(lhs,1_c) ) return rhs;
      else if constexpr( NUCOG_MATCH(rhs,1_c) ) return lhs;
      else return node<tags::times_,XLHS, XRHS>{lhs.self(), rhs.self()};
    }
  }
}


#endif