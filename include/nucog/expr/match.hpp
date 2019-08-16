//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_MATCH_HPP_INCLUDED
#define NUCOG_EXPR_MATCH_HPP_INCLUDED

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

#endif
