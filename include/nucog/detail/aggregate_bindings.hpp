//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_DETAILS_AGGREGATE_BINDINGS_HPP_INCLUDED
#define NUCOG_DETAILS_AGGREGATE_BINDINGS_HPP_INCLUDED

#include <utility>
#include <type_traits>

namespace nucog::detail
{
  // Turn any type into a RegularType info carrier
  template<typename T> struct box {};

  // Aggregate_bindings roll up a list of lambdas and give them a operator(Key)-like interface
  template<typename... Ts>
  struct aggregate_bindings : Ts...
  {
    constexpr aggregate_bindings(Ts const&... t) noexcept : Ts(t)... {}
    constexpr aggregate_bindings(aggregate_bindings const& other) =default;

    using Ts::operator()...;

    struct not_supported_key {};

    template<typename K> constexpr not_supported_key operator()(box<K> const&) const noexcept
    {
      return {};
    }

    template<typename K, typename U>
    constexpr auto operator()(box<K> const& k, U const& u) const noexcept
    {
      // If calling without default would return the key, use the default
      if constexpr( std::is_same_v<decltype(this->operator()(k)),not_supported_key> )
        return u;
      else
        return this->operator()(k);
    }
  };

  template<typename... Ts> aggregate_bindings(Ts...) -> aggregate_bindings<Ts...>;

  // Build the type->value lambda capture
  template<typename Key, typename Value>
  constexpr auto bind(Value&& v) noexcept
  {
    if constexpr( std::is_rvalue_reference_v<Value&&> )
    {
      return [w = std::move(std::forward<Value>(v))](box<Key> const&) -> Value const& { return w; };
    }
    else
    {
      return [&v](box<Key> const&) -> decltype(auto) { return v; };
    }
  }
}

#endif
