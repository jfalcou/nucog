//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_TERMINAL_HPP_INCLUDED
#define NUCOG_EXPR_TERMINAL_HPP_INCLUDED

#include <nucog/detail/helpers.hpp>
#include <nucog/detail/raberu.hpp>
#include <nucog/expr/is_terminal.hpp>
#include <nucog/expr/is_symbol.hpp>
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
  struct any_term;
  struct any_var;
  struct any_lit;

  template<typename Symbol> struct terminal : expr<terminal<Symbol>>
  {
    static constexpr int             arity() noexcept { return 0;  }
    static constexpr tags::terminal_ tag()   noexcept { return {}; }
    static constexpr bool is_placeholder()   noexcept { return false; }

    constexpr terminal() noexcept = default;

    constexpr terminal(Symbol&) =delete;
    constexpr terminal(Symbol const& s) noexcept : value_(s) {}
    constexpr terminal(Symbol&&      s) noexcept : value_(std::move(s)) {}

    constexpr Symbol value() const noexcept { return value_; }

    template<std::size_t Index> constexpr auto get() const noexcept
    {
      // Prevent cascading error messages
      if constexpr(Index == 0)
      {
        return value();
      }
      else
      {
        static_assert(Index == 0, "Invalid child access");
        return *this;
      }
    }

    static constexpr bool match(type_t<any_expr>) noexcept { return true; }
    static constexpr bool match(type_t<any_term>) noexcept { return true; }
    static constexpr bool match(type_t<any_var> ) noexcept { return is_symbol_v<Symbol>;  }
    static constexpr bool match(type_t<any_lit> ) noexcept { return !is_symbol_v<Symbol>; }

    template<typename T>
    constexpr auto operator=(T&& v) const noexcept
    {
      return rbr::keyword<Symbol> = std::forward<T>(v);
    }

    template<typename OtherSymbol>
    static constexpr bool match(type_t<terminal<OtherSymbol>>) noexcept
    {
      return std::is_same_v<Symbol,OtherSymbol>;
    }

    template<typename Other>
    static constexpr bool match(type_t<Other>) noexcept
    {
      return  std::is_same_v<Symbol,Other>;
    }

    Symbol value_;
  };

  //================================================================================================
  // Display support
  template<typename Stream, typename Value>
  Stream& display(Stream& os, tags::terminal_ const&, Value const& v)
  {
    os << v;
    return os;
  }

  //================================================================================================
  // Evaluate support
  template<typename Environment, typename Value>
  constexpr auto evaluate(Environment const& env, tags::terminal_ const&, Value const& v)
  {
    return v;
  }

  template<typename Environment, typename S>
  constexpr auto evaluate(Environment const& env, tags::terminal_ const&, literal::symbol_id<S> const& v)
  {
    constexpr auto other  = terminal<literal::symbol_id<S>>();
    constexpr auto kw     = rbr::keyword<literal::symbol_id<S>>;
    if constexpr( Environment::contains(kw) ) return env[kw]; else  return other;
  }

  //================================================================================================
  // Joker for any term in matcher
  struct any_term : expr<any_term>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_term const term_ = {};

  //================================================================================================
  // Joker for any variable in matcher
  struct any_var : expr<any_var>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_var const var_ = {};

  //================================================================================================
  // Joker for any literal in matcher
  struct any_lit : expr<any_lit>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_lit const lit_ = {};
}

#define NUCOG_SYMNAME(...) NUCOG_CAT(NUCOG_STRING(__VA_ARGS__),_sym)

#ifdef NUCOG_EXPLICIT_SYMBOL
#define NUCOG_SYMBOL(...) ::nucog::terminal<std::decay_t<decltype(NUCOG_SYMNAME(__VA_ARGS__))>>{}
#else
#define $(...)            ::nucog::terminal<std::decay_t<decltype(NUCOG_SYMNAME(__VA_ARGS__))>>{}
#endif

#endif
