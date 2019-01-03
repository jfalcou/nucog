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

#include <nucog/expr/expr.hpp>

namespace nucog::tags
{
  struct minus_ : tag<minus_> {};
}

namespace nucog
{
  template<typename X>
  constexpr auto operator-( expr<X> const& xhs ) noexcept
  {
    return unary<tags::minus_,X>{xhs.self()};
  }

  template<typename XLHS, typename XRHS>
  constexpr auto operator-( expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    return binary<tags::minus_,XLHS, XRHS>{lhs.self(), rhs.self()};
  }
}

#endif
