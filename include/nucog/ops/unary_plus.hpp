//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_UNARY_PLUS_HPP_INCLUDED
#define NUCOG_OPS_UNARY_PLUS_HPP_INCLUDED

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
  struct unary_plus_ : tag<unary_plus_> {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Operator injection
  template<typename XARG> constexpr auto operator+( expr<XARG> const& xhs ) noexcept
  {
    return make(tags::unary_plus_{}, xhs);
  }

  // -----------------------------------------------------------------------------------------------
  // Unary + builder
  template<typename XARG>
  constexpr auto build( tags::unary_plus_ const&, expr<XARG> const& arg ) noexcept
  {
    return node<tags::unary_plus_,XARG>{arg.self()};
  }

  // -----------------------------------------------------------------------------------------------
  // Support for display
  template<> struct display_policy<tags::unary_plus_>
  {
    static constexpr const char*  symbol    = "+";
    static constexpr format       notation  = format::prefix;
  };

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  template<typename C0>
  constexpr auto evaluate(tags::unary_plus_ const&, C0 const& c0)
  {
    return c0;
  }
}

#endif
