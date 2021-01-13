//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

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
#include <nucog/ops/make.hpp>
#include <nucog/ops/times.hpp>
#include <nucog/visitor/display.hpp>

namespace nucog::tags
{
  struct plus_ : tag<plus_> {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Operator injection
  template<typename XLHS, typename XRHS, typename = supports_overload<XLHS,XRHS>>
  constexpr auto operator+( XLHS&& lhs, XRHS&& rhs ) noexcept
  {
    return make(tags::plus_{}, as_expr(std::forward<XLHS>(lhs)), as_expr(std::forward<XRHS>(rhs)));
  }

  // -----------------------------------------------------------------------------------------------
  // Operator+ builder
  template<typename XLHS, typename XRHS>
  constexpr auto build( tags::plus_ const&, expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    using namespace literal;

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
    else if constexpr( NUCOG_MATCH(lhs,lit_ * expr_) && NUCOG_MATCH(rhs,expr_))
    {
      if constexpr( NUCOG_MATCH(lhs[1_c],rhs.self()) )
      {
        using vl = decltype(lhs[0_c].value());
        return idx_<vl::value+1>{} * rhs;
      }
      else
      {
        return node<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
      }
    }
    else if constexpr( NUCOG_MATCH(lhs,expr_) && NUCOG_MATCH(rhs,lit_ * expr_))
    {
      if constexpr( NUCOG_MATCH(lhs.self(),rhs[1_c]) )
      {
        using vr = decltype(rhs[0_c].value());
        return idx_<1+vr::value>{} * lhs;
      }
      else
      {
        return node<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
      }
    }
    else
    {
      return node<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Support for display
  template<> struct display_policy<tags::plus_>
  {
    static constexpr const char*  symbol    = "+";
    static constexpr format       notation  = format::infix;
  };

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  template<typename C0, typename C1>
  constexpr auto evaluate(tags::plus_ const&, C0 const& c0, C1 const& c1)
  {
    return c0 + c1;
  }
}

#endif
