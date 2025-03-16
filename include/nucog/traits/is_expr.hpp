//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>

namespace nucog
{
  template<typename Tree> struct expr;

  template<typename T> struct is_expr : std::is_base_of<expr<T>,T> {};
  template<typename T> struct is_expr<expr<T>> : std::true_type {};
  template<typename T> using is_expr_t = typename is_expr<T>::type;
  template<typename T> constexpr inline auto  is_expr_v = is_expr<T>::value;
}
