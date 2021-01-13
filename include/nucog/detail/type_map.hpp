//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_DETAILS_TYPE_MAP_HPP_INCLUDED
#define NUCOG_DETAILS_TYPE_MAP_HPP_INCLUDED

#include <utility>
#include <type_traits>
#include <nucog/detail/aggregate_bindings.hpp>

namespace nucog::detail
{
  template<typename Storage>
  struct type_map_
  {
    template<typename K>
    constexpr decltype(auto) operator()(K const&) const
    {
      return storage(detail::box<K>{});
    }

    template<typename K, typename U>
    constexpr decltype(auto) operator()(K const&, U const& u) const
    {
      return storage(detail::box<K>{}, u);
    }

    Storage storage;
  };
}

namespace nucog
{
  // Helper function to build a type_map
  template<typename... NamedParams>
  constexpr auto type_map(NamedParams&&... ts) noexcept
  {
    using s_t = decltype(detail::aggregate_bindings( std::forward<NamedParams>(ts)...));
    return detail::type_map_<s_t>{detail::aggregate_bindings(std::forward<NamedParams>(ts)...)};
  }
}

#endif
