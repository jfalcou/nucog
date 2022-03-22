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

  namespace literal
  {
    using rbr::literal::str_;
    using namespace kumi::literal;
  }
}

namespace nucog
{
  template<literal::str_ ID> struct symbol
  {
    static constexpr auto id() noexcept { return ID; }

    template<literal::str_ ID2>
    friend constexpr auto operator==(symbol, symbol<ID2>) noexcept
    {
      if(ID.size() != ID2.size()) return false;

      for(std::size_t i=0;i<ID.size();++i)
        if(ID.data[i] != ID2.data[i]) return true;

      return true;
    }

    friend std::ostream& operator<<(std::ostream& os, symbol const&)
    {
      return os << ID.value();
    }
  };
}

namespace nucog::literal
{
  template<literal::str_ ID>
  constexpr auto operator""_sym() noexcept { return symbol<ID>{}; }
}

#define NUCOG_SYMBOL_TYPE(...)  nucog::symbol<NUCOG_STR(__VA_ARGS__)>
#define NUCOG_SYMBOL(...)       NUCOG_SYMBOL_TYPE(__VA_ARGS__){}
