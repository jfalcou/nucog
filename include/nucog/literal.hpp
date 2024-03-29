//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/detail/helpers.hpp>
#include <type_traits>
#include <utility>
#include <cstdint>
#include <limits>
#include <string>

namespace nucog::literal
{
  // -----------------------------------------------------------------------------------------------
  /*
    String of arbitrary size are turned into a sequence of 64-bits tokens that allow us to
    reconstruct the string later on.
  */
  template<typename HashSequence> struct symbol_id;

  template<std::uint64_t Size, std::uint64_t... Hash>
  struct symbol_id< std::integer_sequence<std::uint64_t, Size, Hash...> >
  {
    using hash_type = std::integer_sequence<std::uint64_t,Hash...>;

    NUCOG_FORCE_INLINE static constexpr auto id() noexcept { return hash_type{}; }

    // Rebuild a dynamic string from the token sequence
    NUCOG_FORCE_INLINE static std::string str()
    {
      char that[Size+1] = {};

      // Variadically iterate over every token
      [&, index = 0ULL](auto... Hs) mutable
      {
        // Unroll the processing of each token
        auto make = [&](auto H)
        {
          // Extract each char inside a uint64_t and place it in the proper index in
          // the output string
          [&]<std::size_t... I>(std::index_sequence<I...>)
          {
            constexpr auto steps = sizeof...(I);
            // We unroll by 8 but we need to protect against out-of-range access
            (( that[(index+I)<Size ? index+I : Size] = (H >> (I*steps)) & 0xFF ), ...);
            index += steps;
          }( std::make_index_sequence<sizeof(std::uint64_t)>{});
        };

        (make(Hs),...);
      }(Hash...);

      return std::string(that, Size);
    }

    template<typename H2> constexpr bool operator==( symbol_id<H2> const& ) const noexcept
    {
      return std::is_same_v<hash_type,typename symbol_id<H2>::hash_type>;
    }

    template<typename H2> constexpr bool operator!=( symbol_id<H2> const& ) const noexcept
    {
      return !std::is_same_v<hash_type,typename symbol_id<H2>::hash_type>;
    }
  };

  /*
    Symbol ID display on standard streams
  */
  template<typename HashSequence>
  std::ostream& operator<<( std::ostream& os, symbol_id<HashSequence> const& sym)
  {
    return os << sym.str();
  }

  /*
    Convert a fragment of 8 characters from an arbitrary variadic sequence of characters
    into a 64-bits token
  */
  template<std::size_t Start, typename... Ts> constexpr auto hash8(Ts... cs) noexcept
  {
    std::uint64_t h     = {};
    std::size_t beg     = Start*8;
    std::size_t end     = std::min(sizeof...(cs),beg+8);
    std::uint64_t chs[] = { static_cast<std::uint64_t>(cs)... };

    for(std::size_t i=beg;i<end;++i)
      h = (h<<8) | chs[end-1-i+beg];

    return h;
  }

  constexpr std::uint64_t hash() noexcept { return 0; }
  /*
    Variadic trampoline that walks through each sequence of 8 characters to compute
    each 64-bits token
  */
  template<typename T, T... C, std::size_t... Offsets>
  constexpr auto hash(std::integer_sequence<T, C...>, std::index_sequence<Offsets...>) noexcept
  {
    return std::integer_sequence<std::uint64_t,sizeof...(C),hash8<Offsets>(C...)...>{};
  }

  /*
    Compute how many 64-bits hash tokens are required to encode the symbol name
    in a bijective way.
  */
  constexpr std::size_t nb_tokens(std::size_t n)
  {
    constexpr auto bits  = std::numeric_limits<unsigned char>::digits;
    constexpr auto bytes = std::numeric_limits<std::uint64_t>::digits/bits;
    return (n+bytes-1)/bytes;
  }

  // Turn "A string" into a constexpr sequence of 64-bits bijective hashes
  template<typename T, T... C>
  constexpr symbol_id < decltype( hash( std::integer_sequence<T,C...>{}
                                      , std::make_index_sequence<nb_tokens(sizeof...(C))>{}
                                      )
                                )
                      > operator"" _sym() noexcept
  {
    return {};
  }

  // -----------------------------------------------------------------------------------------------
  // Literal integral constants
  template<std::uint64_t N> using idx_ = std::integral_constant<std::uint64_t,N>;

  template<char... c> constexpr std::uint64_t chars_to_int()
  {
    std::uint64_t value = 0;
    char arr[] = {c...};
    for(std::size_t i = 0;i<sizeof...(c);++i) value = value*10 + (arr[i] - '0');
    return value;
  }

  template<char ...c> constexpr auto operator"" _c() noexcept
  {
    return idx_<chars_to_int<c...>()>{};
  }
}
