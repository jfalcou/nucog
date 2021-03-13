//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>

namespace nucog
{
  /*
    make is the entry point for optimized expression creation
    It checks if the requested AST contains placeholder and, if not, proceed with the user-defined
    builder calls.
  */
  template<typename Tag, typename... XARGS>
  constexpr auto make( Tag const&, expr<XARGS> const&... args ) noexcept
  {
    if constexpr( (XARGS::is_placeholder() || ...) )
    {
      return node<Tag,XARGS...>{args.self()...};
    }
    else
    {
      return build( Tag{}, args...);
    }
  }
}
