//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_IS_EXPR_HPP_INCLUDED
#define NUCOG_EXPR_IS_EXPR_HPP_INCLUDED

#include <type_traits>

namespace nucog
{
  template<typename T>
  struct is_expr : std::is_base_of<expr<T>,T>
  {};

  template<typename T> using is_expr_t = typename is_expr<T>::type;

  template<typename T> constexpr inline auto  is_expr_v = is_expr<T>::value;
}

#endif
