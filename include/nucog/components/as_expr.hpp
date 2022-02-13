//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <nucog/components/terminal.hpp>
#include <nucog/deps/detail.hpp>
#include <nucog/traits/is_expr.hpp>
#include <nucog/traits/is_terminal.hpp>

namespace nucog
{
  template<typename T>
  NUCOG_FORCE_INLINE constexpr decltype(auto) as_expr(T&& x) noexcept
  {
    using t_t = std::remove_cvref_t<T>;
    if constexpr(is_expr_v<t_t> || is_terminal_v<t_t>)  return NUCOG_FWD(x);
    else                                                return terminal<t_t>(NUCOG_FWD(x));
  }
}
