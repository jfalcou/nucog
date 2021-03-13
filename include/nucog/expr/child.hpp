//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_CHILD_HPP_INCLUDED
#define NUCOG_EXPR_CHILD_HPP_INCLUDED

#include <cstddef>
#include <utility>

namespace nucog
{
  template<std::size_t Index, typename Expression>
  constexpr auto child(Expression const& expr) noexcept
  {
    return expr.template get<Index>();
  }
}

#endif
