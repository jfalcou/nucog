//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
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
