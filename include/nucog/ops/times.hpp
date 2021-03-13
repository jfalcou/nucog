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
#include <nucog/expr/match.hpp>
#include <nucog/expr/child.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/ops/make.hpp>
#include <nucog/literal.hpp>
#include <nucog/visitor/display.hpp>

namespace nucog::tags
{
  struct times_ : tag<times_>
  {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Support for display
  template<> struct display_policy<tags::times_>
  {
    static constexpr const char*  symbol    = "*";
    static constexpr format       notation  = format::infix;
  };

  template<typename XLHS, typename XRHS, typename = supports_overload<XLHS,XRHS>>
  constexpr auto operator*( XLHS&& lhs, XRHS&& rhs ) noexcept
  {
    return make(tags::times_{}, as_expr(std::forward<XLHS>(lhs)), as_expr(std::forward<XRHS>(rhs)));
  }
}

// -------------------------------------------------------------------------------------------------
// Optimization
namespace nucog
{
  template<typename XLHS, typename XRHS>
  constexpr auto build( tags::times_ const&, expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    using namespace literal;

    if constexpr( NUCOG_MATCH(lhs,0_c) || NUCOG_MATCH(rhs,0_c) ) return 0_c;
    else if constexpr( NUCOG_MATCH(lhs,1_c) ) return rhs;
    else if constexpr( NUCOG_MATCH(rhs,1_c) ) return lhs;
    else return node<tags::times_,XLHS, XRHS>{lhs.self(), rhs.self()};
  }
}

// -------------------------------------------------------------------------------------------------
// Evaluation support
namespace nucog
{
  template<typename C0, typename C1>
  constexpr auto evaluate(tags::times_ const&, C0 const& c0, C1 const& c1)
  {
    return c0 * c1;
  }
}
