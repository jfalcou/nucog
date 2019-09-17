//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_UNARY_MINUS_HPP_INCLUDED
#define NUCOG_OPS_UNARY_MINUS_HPP_INCLUDED

#include <nucog/detail/supports_overload.hpp>
#include <nucog/expr/as_expr.hpp>
#include <nucog/expr/match.hpp>
#include <nucog/expr/child.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/literal.hpp>
#include <nucog/ops/make.hpp>
#include <nucog/ops/times.hpp>
#include <nucog/visitor/display.hpp>

namespace nucog::tags
{
  struct unary_minus_ : tag<unary_minus_> {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Operator injection
  template<typename XARG>
  constexpr auto operator-( expr<XARG> const& arg ) noexcept
  {
    return make(tags::unary_minus_{}, arg);
  }

  // -----------------------------------------------------------------------------------------------
  // Operator- builder
  template<typename XARG>
  constexpr auto build( tags::unary_minus_ const&, expr<XARG> const& arg ) noexcept
  {
    return node<tags::unary_minus_,XARG>{arg.self()};
  }

  // -----------------------------------------------------------------------------------------------
  // Support for display
  template<> struct display_policy<tags::unary_minus_>
  {
    static constexpr const char*  symbol    = "-";
    static constexpr format       notation  = format::infix;
  };

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  template<typename C0>
  constexpr auto evaluate(tags::unary_minus_ const&, C0 const& c0)
  {
    return -c0;
  }
}

#endif
