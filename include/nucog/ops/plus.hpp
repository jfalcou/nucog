//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_PLUS_HPP_INCLUDED
#define NUCOG_OPS_PLUS_HPP_INCLUDED

#include <nucog/detail/supports_overload.hpp>
#include <nucog/expr/as_expr.hpp>
#include <nucog/expr/child.hpp>
#include <nucog/expr/match.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/literal.hpp>
#include <nucog/ops/times.hpp>

namespace nucog::tags
{
  struct plus_ : tag<plus_>
  {};

  // Unary + default generator
  template<typename ARG>
  constexpr auto make( plus_ const&, expr<ARG> const& arg ) noexcept
  {
    return node<tags::plus_,ARG>{arg.self()};
  }
}

namespace nucog
{
  template<typename X> constexpr auto operator+( expr<X> const& xhs ) noexcept
  {
    return make(tags::plus_{}, xhs);
  }

  template<typename XLHS, typename XRHS, typename = supports_overload<XLHS,XRHS>>
  constexpr auto operator+( XLHS&& lhs, XRHS&& rhs ) noexcept
  {
    return make(tags::plus_{}, as_expr(std::forward<XLHS>(lhs)), as_expr(std::forward<XRHS>(rhs)));
  }
}

// -------------------------------------------------------------------------------------------------
// Optimization
namespace nucog::tags
{
  template<typename XLHS, typename XRHS>
  constexpr auto make( plus_ const&, expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    using namespace literal;

    if constexpr( XLHS::is_placeholder() || XRHS::is_placeholder() )
    {
      return node<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
    }
    else
    {
      if      constexpr( NUCOG_MATCH(lhs,rhs) ) return 2_c * lhs;
      else if constexpr( NUCOG_MATCH(lhs,0_c) ) return rhs;
      else if constexpr( NUCOG_MATCH(rhs,0_c) ) return lhs;
      else if constexpr( NUCOG_MATCH(lhs,lit_ * expr_) && NUCOG_MATCH(rhs,lit_ * expr_))
      {
        if constexpr( NUCOG_MATCH(lhs[1_c],rhs[1_c]) )
        {
          using vl = decltype(lhs[0_c].value());
          using vr = decltype(rhs[0_c].value());

          return idx_<vl::value+vr::value>{} * lhs[1_c];
        }
        else
        {
          return node<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
        }
      }
      else return node<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
    }
  }
}

#endif
