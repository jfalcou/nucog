//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_MAKE_HPP_INCLUDED
#define NUCOG_OPS_MAKE_HPP_INCLUDED

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

#endif
