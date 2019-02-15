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

#include <nucog/expr/expr.hpp>
#include <cstddef>
#include <tuple>

namespace nucog
{
  template<typename Tag, typename... Children> struct node;

  // Overload for unary node
  template<typename Tag, typename Child> struct node<Tag, Child> : expr<node<Tag, Child>>
  {
    explicit node(Child const& c) noexcept : child0_(c) {}

    static constexpr int arity() noexcept { return 1;  }
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

  // Overload for binary node
  template<typename Tag, typename Child0, typename Child1>
  struct node<Tag, Child0, Child1> : expr<node<Tag, Child0, Child1>>
  {
    node(Child0 const& c0, Child1 const& c1) : child0_(c0), child1_(c1) {}

    static constexpr int  arity() noexcept { return 2;  }
    static constexpr Tag  tag()   noexcept { return {}; }

    template<std::size_t Index> constexpr auto const& child() const noexcept
    {
      static_assert(Index < 2, "Invalid child access");
      if constexpr( Index == 0) return child0_;
      if constexpr( Index == 1) return child1_;
    }

    template<std::size_t Index> constexpr auto& child() noexcept
    {
      static_assert(Index < 2, "Invalid child access");
      if constexpr( Index == 0) return child0_;
      if constexpr( Index == 1) return child1_;
    }

    private:
    Child0 child0_;
    Child1 child1_;
  };

  // Basic case
  template<typename Tag, typename... Children>
  struct node : expr<node<Tag, Children...>>
  {
    node(Children const&... cs) : children_(cs...) {}

    static constexpr int  arity() noexcept { return sizeof...(Children);  }
    static constexpr Tag  tag()   noexcept { return {}; }

    template<std::size_t Index> constexpr auto const& child() const noexcept
    {
      // Prevent cascading error messages
      if constexpr(Index < arity())
      {
        return std::get<Index>(children_);
      }
      else
      {
        static_assert(Index < arity(), "Invalid child access");
        return *this;
      }
    }

    template<std::size_t Index> constexpr auto& child() noexcept
    {
      // Prevent cascading error messages
      if constexpr(Index < arity())
      {
        return std::get<Index>(children_);
      }
      else
      {
        static_assert(Index < arity(), "Invalid child access");
        return *this;
      }
    }

    private:
    std::tuple<Children...> children_;
  };
}

#endif
