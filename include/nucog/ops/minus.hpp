//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_MINUS_HPP_INCLUDED
#define NUCOG_OPS_MINUS_HPP_INCLUDED

#include <nucog/detail/supports_overload.hpp>
#include <nucog/expr/as_expr.hpp>
#include <nucog/expr/child.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/literal.hpp>
#include <nucog/ops/times.hpp>

namespace nucog::tags
{
  struct minus_ : tag<minus_>
  {};

  // Unary - default generator
  template<typename ARG>
  constexpr auto make( minus_ const&, expr<ARG> const& arg ) noexcept
  {
    return node<tags::minus_,ARG>{arg.self()};
  }

  // Binary - default generator
  template<typename XLHS, typename XRHS>
  constexpr auto make( minus_ const&, expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    return node<tags::minus_,XLHS, XRHS>{lhs.self(), rhs.self()};
  }
}

namespace nucog
{
  template<typename X> constexpr auto operator-( expr<X> const& xhs ) noexcept
  {
    return make(tags::minus_{}, xhs);
  }

  template<typename XLHS, typename XRHS, typename = supports_overload<XLHS,XRHS>>
  constexpr auto operator-( XLHS const& lhs, XRHS const& rhs ) noexcept
  {
    return make(tags::minus_{}, as_expr(lhs), as_expr(rhs));
  }
}

// -------------------------------------------------------------------------------------------------
// Optimization
namespace nucog::tags
{
  template<typename X>
  constexpr auto make( minus_ const&, expr<X> const&, expr<X> const& ) noexcept
  {
    using namespace literal;
    return 0_c;
  }

  template<std::uint64_t N, std::uint64_t M, typename X>
  constexpr auto make ( minus_ const&
                      , expr<node<tags::times_,terminal<literal::idx_<N>>,X>> const& lhs
                      , expr<node<tags::times_,terminal<literal::idx_<M>>,X>> const&
                      ) noexcept
  {
    return as_expr(literal::idx_<N-M>{}) * child<1>(lhs);
  }
}

#endif
