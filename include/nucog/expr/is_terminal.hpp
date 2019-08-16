//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_IS_TERMINAL_HPP_INCLUDED
#define NUCOG_EXPR_IS_TERMINAL_HPP_INCLUDED

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

#endif
