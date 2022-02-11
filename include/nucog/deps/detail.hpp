//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#define NUCOG_STR(...)   NUCOG_STR_((__VA_ARGS__))
#define NUCOG_STR__(...) #__VA_ARGS__
#define NUCOG_STR_(TXT)  NUCOG_STR__ TXT

#define NUCOG_CAT(x, y)   NUCOG_CAT_I(x, y)
#define NUCOG_CAT_I(x, y) x ## y

#ifdef __MSVC__
#define NUCOG_FORCE_INLINE __forceinline
#else
#define NUCOG_FORCE_INLINE __attribute__((always_inline))
#endif

namespace nucog
{
  template<typename T> struct type_t { using type = T; };
}
