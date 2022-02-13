//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <nucog/traits/is_expr.hpp>
#include <nucog/traits/is_symbol.hpp>

namespace nucog
{
  template<typename Arg>
  concept supports_overload = is_expr_v<std::decay_t<Arg>> || is_symbol_v<std::decay_t<Arg>>;
}
