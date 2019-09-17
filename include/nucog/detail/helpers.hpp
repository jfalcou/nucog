//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_DETAIL_HELPERS_HPP_INCLUDED
#define NUCOG_DETAIL_HELPERS_HPP_INCLUDED

#include <cstddef>
#include <utility>

// Turn a variadic macro calls into a string containing properly placed commas
#define NUCOG_STRING(...)   NUCOG_STRING_((__VA_ARGS__))
#define NUCOG_STRING__(...) #__VA_ARGS__
#define NUCOG_STRING_(TXT)  NUCOG_STRING__ TXT

// Safely concatenate macro params
#define NUCOG_CAT(x, y) NUCOG_CAT_I(x, y)
#define NUCOG_CAT_I(x, y) x ## y

// Portabel force-inline
#ifdef __MSVC__
#define NUCOG_FORCE_INLINE __forceinline
#else
#define NUCOG_FORCE_INLINE __attribute__((always_inline))
#endif

namespace nucog
{
  template<typename Type> struct type_t {};
}

#ifdef NUCOG_EXPLICIT_SYMBOL
#define NUCOG_TYPE(E) ::nucog::type_t<std::decay_t<decltype(E)>>{}
#else
#define $$(E) ::nucog::type_t<std::decay_t<decltype(E)>>{}
#endif


namespace nucog::detail
{
  // Tuple-free apply
  template<typename Func, std::size_t... I>
  NUCOG_FORCE_INLINE
  constexpr decltype(auto)apply_impl(Func&& f, std::index_sequence<I...> const&)
  noexcept(noexcept(std::forward<Func>(f)(std::integral_constant<std::size_t,I>{}...)))
  {
    return std::forward<Func>(f)(std::integral_constant<std::size_t,I>{}...);
  }

  template<std::size_t Count,typename Func>
  NUCOG_FORCE_INLINE  constexpr decltype(auto) apply(Func&& f)
  noexcept(noexcept(apply_impl(std::forward<Func>(f), std::make_index_sequence<Count>{})))
  {
    return apply_impl(std::forward<Func>(f), std::make_index_sequence<Count>{});
  }
}

#endif
