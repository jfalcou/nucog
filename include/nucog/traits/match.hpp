//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace nucog
{
  template<typename E1, typename E2>
  constexpr bool match(E1 const&, E2 const&) noexcept
  {
    if constexpr(E1::is_placeholder())  return E2::match(E1{});
    else                                return E1::match(E2{});
  }
}
