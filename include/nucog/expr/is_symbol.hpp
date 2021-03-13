//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>

namespace nucog::literal
{
  template<typename HashSequence> struct symbol_id;
}

namespace nucog
{
  template<typename T>      struct is_symbol                                    : std::false_type {};
  template<typename Symbol> struct is_symbol<literal::symbol_id<Symbol>       > : std::true_type  {};
  template<typename Symbol> struct is_symbol<literal::symbol_id<Symbol> const > : std::true_type  {};
  template<typename Symbol> struct is_symbol<literal::symbol_id<Symbol> const&> : std::true_type  {};
  template<typename Symbol> struct is_symbol<literal::symbol_id<Symbol> &     > : std::true_type  {};
  template<typename Symbol> struct is_symbol<literal::symbol_id<Symbol> &&    > : std::true_type  {};

  template<typename T> using is_symbol_t = typename is_symbol<T>::type;
  template<typename T> constexpr inline auto is_symbol_v = is_symbol<T>::value;
}
