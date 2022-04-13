//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <nucog/deps/detail.hpp>
#include <type_traits>

namespace nucog
{
  template<typename P, typename E>
  constexpr bool match(P const&, E const&) noexcept
  {
    return E::match(P{});
  }

  template<typename P, typename... Es>
  constexpr bool matches(P const& p, Es const&... es) noexcept
  {
    return (match(p,es) && ... && true);
  }
}
