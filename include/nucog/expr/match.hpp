//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/detail/helpers.hpp>

namespace nucog
{
  template<typename T, typename U>
  constexpr bool match( type_t<T>, type_t<U> u)
  {
    return T::match(u);
  }
}

#ifdef NUCOG_EXPLICIT_SYMBOL
#define NUCOG_MATCH( EXPR, PATTERN ) ::nucog::match( NUCOG_TYPE(EXPR),NUCOG_TYPE(PATTERN) )
#else
#define NUCOG_MATCH( EXPR, PATTERN ) ::nucog::match( $$(EXPR), $$(PATTERN) )
#endif
