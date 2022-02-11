//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <nucog/components/tag.hpp>

namespace nucog::tags
{
  struct terminal_ : tag<terminal_> {};
}

namespace nucog
{
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
      return (kw = std::forward<T>(v));
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
}
