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
  template<typename Symbol> struct terminal;

  template<typename T>      struct is_terminal                          : std::false_type {};
  template<typename Symbol> struct is_terminal<terminal<Symbol>       > : std::true_type  {};
  template<typename Symbol> struct is_terminal<terminal<Symbol> const > : std::true_type  {};
  template<typename Symbol> struct is_terminal<terminal<Symbol> const&> : std::true_type  {};
  template<typename Symbol> struct is_terminal<terminal<Symbol> &     > : std::true_type  {};
  template<typename Symbol> struct is_terminal<terminal<Symbol> &&    > : std::true_type  {};

  template<typename T> using is_terminal_t = typename is_terminal<T>::type;
  template<typename T> constexpr inline auto is_terminal_v = is_terminal<T>::value;
}
