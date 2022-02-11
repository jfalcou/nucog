//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
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

    friend std::ostream& operator<<(std::ostream& os, symbol const&)
    {
      for(auto e : ID.data) os << e;
      return os;
    }
  };
}

namespace nucog::literals
{
  template<str_ ID> constexpr auto operator""_sym() noexcept { return symbol<ID>{}; }
}

#define NUCOG_SYMBOL(...) NUCOG_CAT(NUCOG_STR(__VA_ARGS__),_sym)
