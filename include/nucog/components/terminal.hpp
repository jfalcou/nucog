//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <nucog/components/tag.hpp>
#include <nucog/components/expr.hpp>
#include <nucog/components/literal.hpp>
#include <nucog/traits/is_symbol.hpp>

namespace nucog
{
  namespace tags
  {
    struct terminal_ : tag<terminal_> {};
  }
/*
  struct any_term;
  struct any_var;
  struct any_lit;
*/
  template<typename Symbol> struct terminal : expr<terminal<Symbol>>
  {
    static constexpr int             arity() noexcept { return 0;  }
    static constexpr tags::terminal_ tag()   noexcept { return {}; }
    static constexpr bool is_placeholder()   noexcept { return false; }

    constexpr terminal() noexcept = default;

    constexpr auto value() const noexcept { return value_; }

    template<std::size_t Index> constexpr auto get() const noexcept
    {
      if constexpr(Index == 0) return value_;
      else
      {
        static_assert(Index == 0, "Invalid child access");
        return *this;
      }
    }

    template<typename Stream>
    friend Stream& operator<<(Stream& os, terminal const& v)
    requires requires(Stream& s, Symbol const& v) { s << v; }
    {
      return os << v.value_;
    }

/*
    static constexpr bool match(type_t<any_expr>) noexcept { return true; }
    static constexpr bool match(type_t<any_term>) noexcept { return true; }
    static constexpr bool match(type_t<any_var> ) noexcept { return is_symbol_v<Symbol>;  }
    static constexpr bool match(type_t<any_lit> ) noexcept { return !is_symbol_v<Symbol>; }
*/

    template<typename T>
    constexpr auto operator=(T&& v) const noexcept
    requires is_symbol_v<Symbol>
    {
      constexpr auto kw = rbr::keyword(Symbol{});
      return (kw = NUCOG_FWD(v));
    }
/*
    template<auto OtherSymbol>
    static constexpr bool match(type_t<terminal<OtherSymbol>>) noexcept
    {
      return Symbol == OtherSymbol;
    }

    template<typename Other>
    static constexpr bool match(type_t<Other>) noexcept
    {
      return Symbol == Other{};
    }
*/
    Symbol value_;
  };

  //================================================================================================
  // Evaluate support
  template<typename Environment, typename Value>
  constexpr auto evaluate(Environment const&, tags::terminal_ const&, Value const& v)
  {
    return v;
  }

  template<typename Environment, literals::str_ S>
  constexpr auto evaluate(Environment const& env, tags::terminal_ const&, symbol<S> const&)
  {
    constexpr auto other  = terminal<symbol<S>>();
    constexpr auto kw     = rbr::keyword(S);
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

#define NUCOG_TERMINAL(...) ::nucog::terminal<NUCOG_SYMBOL_TYPE(__VA_ARGS__)>{}

#if !defined(NUCOG_EXPLICIT_TERMINAL)
#define $(...)              NUCOG_TERMINAL(__VA_ARGS__)
#endif

