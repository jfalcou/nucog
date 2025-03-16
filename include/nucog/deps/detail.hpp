//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#define NUCOG_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

#define NUCOG_STR(...)   NUCOG_STR_((__VA_ARGS__))
#define NUCOG_STR__(...) #__VA_ARGS__
#define NUCOG_STR_(TXT)  NUCOG_STR__ TXT

#define NUCOG_CAT(x, y)   NUCOG_CAT_I(x, y)
#define NUCOG_CAT_I(x, y) x ## y

#if defined(_MSC_VER)
#  define NUCOG_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#  define NUCOG_FORCEINLINE inline __attribute__((__always_inline__))
#else
#  define NUCOG_FORCEINLINE inline
#endif
