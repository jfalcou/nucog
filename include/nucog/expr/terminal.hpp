//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_TERMINAL_HPP_INCLUDED
#define NUCOG_EXPR_TERMINAL_HPP_INCLUDED

#include <nucog/detail/helpers.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/literal.hpp>

namespace nucog::tags
{
  struct terminal_ : tag<terminal_> {};
}

namespace nucog
{
  template<typename Symbol>
  struct terminal : expr<terminal<Symbol>>
  {
    constexpr int             arity() const noexcept { return 0;  }
    constexpr Symbol          value() const noexcept { return {}; }
    constexpr tags::terminal_ tag()   const noexcept { return {}; }
  };
}

#define NUCOG_SYMNAME(...) NUCOG_CAT(NUCOG_STRING(__VA_ARGS__),_sym)

#ifdef NUCOG_EXPLICIT_SYMBOL
#define NUCOG_SYMBOL(...) ::nucog::terminal<std::decay_t<decltype(NUCOG_SYMNAME(__VA_ARGS__))>>{}
#else
#define $(...)            ::nucog::terminal<std::decay_t<decltype(NUCOG_SYMNAME(__VA_ARGS__))>>{}
#endif

#endif
