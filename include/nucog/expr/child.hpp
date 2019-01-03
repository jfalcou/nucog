//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
  constexpr decltype(auto) child(Expression&& expr) noexcept
  {
    return std::forward<Expression>(expr).template child<Index>();
  }
}

#endif
