//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/detail/helpers.hpp>
#include <nucog/expr/is_expr.hpp>
#include <nucog/expr/is_terminal.hpp>
#include <nucog/expr/terminal.hpp>
#include <type_traits>
#include <utility>

namespace nucog
{
  template<typename T> NUCOG_FORCE_INLINE constexpr decltype(auto) as_expr(T&& x) noexcept
  {
    using t_t = std::decay_t<T>;
    if constexpr(is_expr_v<t_t> || is_terminal_v<t_t>)  return std::forward<T>(x);
    else                                                return terminal<t_t>(std::forward<T>(x));
  }
}
