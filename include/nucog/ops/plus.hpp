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

#include <nucog/expr/expr.hpp>

namespace nucog::tags
{
  struct plus_ : tag<plus_> {};
}

namespace nucog
{
  template<typename X>
  constexpr auto operator+( expr<X> const& xhs ) noexcept
  {
    return unary<tags::plus_,X>{xhs.self()};
  }

  template<typename XLHS, typename XRHS>
  constexpr auto operator+( expr<XLHS> const& lhs, expr<XRHS> const& rhs ) noexcept
  {
    return binary<tags::plus_,XLHS, XRHS>{lhs.self(), rhs.self()};
  }
}

#endif
