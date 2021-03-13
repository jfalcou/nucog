//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_IS_SYMBOL_HPP_INCLUDED
#define NUCOG_EXPR_IS_SYMBOL_HPP_INCLUDED

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

#endif
