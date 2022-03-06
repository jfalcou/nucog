//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/deps/detail.hpp>
#include <nucog/deps/raberu.hpp>
#include <nucog/deps/kumi.hpp>
#include <ostream>

namespace nucog
{
  using kumi::index_t;
  using kumi::index;

  namespace literals
  {
    using rbr::literals::str_;
    using namespace kumi::literals;
  }
}

namespace nucog
{
  template<literals::str_ ID> struct symbol
  {
    static constexpr auto id() noexcept { return ID; }

    template<literals::str_ ID2>
    friend constexpr auto operator==(symbol, symbol<ID2>) noexcept
    {
      return ID.data == ID2.data;
    }

    friend std::ostream& operator<<(std::ostream& os, symbol const&)
    {
      for(auto e : ID.data) os << e;
      return os;
    }
  };
}

namespace nucog::literals
{
  template<literals::str_ ID>
  constexpr auto operator""_sym() noexcept { return symbol<ID>{}; }
}

#define NUCOG_SYMBOL_TYPE(...)  nucog::symbol<NUCOG_STR(__VA_ARGS__)>
#define NUCOG_SYMBOL(...)       NUCOG_SYMBOL_TYPE(__VA_ARGS__){}
