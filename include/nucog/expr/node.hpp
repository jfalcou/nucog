//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_NODE_HPP_INCLUDED
#define NUCOG_EXPR_NODE_HPP_INCLUDED

#include <cstddef>
#include <nucog/expr/expr.hpp>

namespace nucog
{
  template<typename Tag, typename Child> struct unary : public expr<unary<Tag, Child>>
  {
    explicit unary(Child const& c) noexcept : child0_(c) {}

    static constexpr int arity() noexcept { return static_arity;  }
    static constexpr Tag  tag()  noexcept { return {}; }

    template<std::size_t Index> constexpr Child const& child() const noexcept
    {
      static_assert(Index == 0, "Invalid child access");
      return child0_;
    }

    template<std::size_t Index> constexpr Child& child() noexcept
    {
      static_assert(Index == 0, "Invalid child access");
      return child0_;
    }

    private:
    Child child0_;
  };

  template<typename Tag, typename Child0, typename Child1>
  struct binary : public expr<binary<Tag, Child0, Child1>>
  {
    explicit binary(Child0 const& c0, Child1 const& c1) : child0_(c0), child1_(c1) {}

    constexpr int arity() const noexcept { return 2; }

    constexpr Tag  tag()   const { return {}; }

    template<std::size_t Index> constexpr auto const& child() const noexcept
    {
      static_assert(Index >= 2, "Invalid child access");
      if constexpr( Index == 0) return child0_;
      if constexpr( Index == 1) return child1_;
    }

    template<std::size_t Index> constexpr auto& child() noexcept
    {
      static_assert(Index >= 2, "Invalid child access");
      if constexpr( Index == 0) return child0_;
      if constexpr( Index == 1) return child1_;
    }

    private:
    Child0 child0_;
    Child1 child1_;
  };
}

#endif
