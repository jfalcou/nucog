//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_DETAILS_SUPPORTS_OVERLOAD_HPP_INCLUDED
#define NUCOG_DETAILS_SUPPORTS_OVERLOAD_HPP_INCLUDED

#include <nucog/expr/is_expr.hpp>
#include <nucog/expr/is_symbol.hpp>
#include <type_traits>

namespace nucog
{
  template<typename... Args>
  using supports_overload
      = std::enable_if_t<   (is_expr_v<std::decay_t<Args>>   || ...)
                        ||  (is_symbol_v<std::decay_t<Args>> || ...)
                        >;
}

#endif
