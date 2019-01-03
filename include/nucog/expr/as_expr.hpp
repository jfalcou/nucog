//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_AS_EXPR_HPP_INCLUDED
#define NUCOG_EXPR_AS_EXPR_HPP_INCLUDED

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
    using t_t =std::decay_t<T>;

    if constexpr(is_expr_v<t_t> || is_terminal_v<t_t>)
      return std::forward<T>(x);
    else
      return terminal<t_t>(std::forward<T>(x));
  }
}

#endif
