//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/components/node.hpp>

namespace nucog
{
  // make is the entry point for optimized expression creation
  // It checks if the requested AST contains placeholder and, if not, proceed with the user-defined
  // builder calls.
  template<typename Tag, typename... Args>
  NUCOG_FORCEINLINE constexpr auto make( Tag const&, expr<Args> const&... args ) noexcept
  {
    if constexpr( (Args::is_placeholder() || ...) ) return node<Tag,Args...>{args.self()...};
    else                                            return Tag::build(args...);
  }
}
