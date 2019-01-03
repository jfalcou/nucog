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

namespace nucog::literal
{
  template<std::uint64_t Hash>
  struct symbol_id
  {
    static constexpr auto id() noexcept { return Hash; }
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
}

#endif
