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
#include <nucog/expr/child.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/literal.hpp>

namespace nucog::tags
{
  struct times_ : tag<times_> {};

  // Binary *  default generator
  template<typename XLHS, typename XRHS>
  constexpr auto make( times_ const&, expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    return node<tags::times_,XLHS, XRHS>{lhs.self(), rhs.self()};
  }
}

namespace nucog
{
  template<typename XLHS, typename XRHS, typename = supports_overload<XLHS,XRHS>>
  constexpr auto operator*( XLHS const& lhs, XRHS const& rhs ) noexcept
  {
    return make(tags::times_{}, as_expr(lhs), as_expr(rhs));
  }
}

// -------------------------------------------------------------------------------------------------
// Optimization
namespace nucog::tags
{

 template<std::uint64_t N, std::uint64_t M, typename X>
  constexpr auto make ( times_ const&
                      , expr<terminal<literal::idx_<N>>> const& lhs
                      , expr<node<tags::times_,terminal<literal::idx_<M>>,X>> const& rhs
                      ) noexcept
  {
    return literal::idx_<N*M>{} * child<1>(rhs);
  }

  template<typename X>
  constexpr auto make ( times_ const&
                      , expr<terminal<literal::idx_<0>>> const& lhs
                      , expr<X> const& rhs
                      ) noexcept
  {
    using namespace literal;
    return 0_c;
  }

  template<typename X>
  constexpr auto make ( times_ const&
                      , expr<terminal<literal::idx_<1>>> const& lhs
                      , expr<X> const& rhs
                      ) noexcept
  {
    return rhs.self();
  }
}

#endif
