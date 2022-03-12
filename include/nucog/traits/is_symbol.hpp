//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/components/literal.hpp>
#include <type_traits>

namespace nucog
{
  template<typename T>  struct is_symbol                                  : std::false_type {};
  template<literal::str_ Symbol> struct is_symbol<symbol<Symbol>       > : std::true_type  {};
  template<literal::str_ Symbol> struct is_symbol<symbol<Symbol> const > : std::true_type  {};
  template<literal::str_ Symbol> struct is_symbol<symbol<Symbol> const&> : std::true_type  {};
  template<literal::str_ Symbol> struct is_symbol<symbol<Symbol> &     > : std::true_type  {};
  template<literal::str_ Symbol> struct is_symbol<symbol<Symbol> &&    > : std::true_type  {};

  template<typename T> using is_symbol_t = typename is_symbol<T>::type;

  template<typename T> constexpr inline auto is_symbol_v = is_symbol<T>::value;
}
