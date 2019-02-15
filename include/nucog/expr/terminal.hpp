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
#include <utility>

namespace nucog::tags
{
  struct terminal_ : tag<terminal_> {};
}

namespace nucog
{
  template<typename Symbol> struct terminal : expr<terminal<Symbol>>
  {
    static constexpr int             arity() noexcept { return 0;  }
    static constexpr tags::terminal_ tag()   noexcept { return {}; }

    terminal() noexcept = default;

    terminal(Symbol const& s) noexcept : value_(s) {}
    terminal(Symbol&&      s) noexcept : value_(std::move(s)) {}

    constexpr Symbol value() const noexcept { return value_; }

    // No child can be retrieved from terminal - use value()
    template<std::size_t Index> constexpr Symbol const& child() const noexcept = delete;
    template<std::size_t Index> constexpr Symbol&       child()       noexcept = delete;

    Symbol value_;
  };
}

#define NUCOG_SYMNAME(...) NUCOG_CAT(NUCOG_STRING(__VA_ARGS__),_sym)

#ifdef NUCOG_EXPLICIT_SYMBOL
#define NUCOG_SYMBOL(...) ::nucog::terminal<std::decay_t<decltype(NUCOG_SYMNAME(__VA_ARGS__))>>{}
#else
#define $(...)            ::nucog::terminal<std::decay_t<decltype(NUCOG_SYMNAME(__VA_ARGS__))>>{}
#endif

#endif
