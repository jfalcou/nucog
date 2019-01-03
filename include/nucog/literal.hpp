//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_LITERAL_HPP_INCLUDED
#define NUCOG_LITERAL_HPP_INCLUDED

#include <cstdint>
#include <type_traits>

namespace nucog::literal
{
  // -----------------------------------------------------------------------------------------------
  // Symbol hashing from literal string
  template<std::uint64_t Hash>
  struct symbol_id
  {
    static constexpr auto id() noexcept { return Hash; }

    template<std::uint64_t H2> constexpr bool operator==( symbol_id<H2> const& ) const noexcept
    {
      return Hash == H2;
    }

    template<std::uint64_t H2> constexpr bool operator!=( symbol_id<H2> const& ) const noexcept
    {
      return Hash != H2;
    }
  };

  template<typename... T > constexpr std::uint64_t hash(T... c) noexcept
  {
      std::uint64_t hash = 0;
      ((hash += c, hash += (hash << 10), hash ^= (hash >> 6)),...);
      hash += (hash << 3);
      hash ^= (hash >> 11);
      hash += (hash << 15);
      return hash;
  }

  template<typename T, T... c> constexpr symbol_id<hash(c...)> operator"" _sym() noexcept
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

#endif
