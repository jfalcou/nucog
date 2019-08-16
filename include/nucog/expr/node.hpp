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

#include <nucog/expr/child.hpp>
#include <nucog/expr/expr.hpp>
#include <cstddef>
#include <tuple>

namespace nucog
{
  //================================================================================================
  // Joker for any node in matcher
  template<int Arity> struct any_node : expr<any_node<Arity>>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_node<1> const unary_expr_    = {};
  inline constexpr any_node<2> const binary_expr_   = {};
  inline constexpr any_node<3> const ternary_expr_  = {};

  template<int N>
  inline constexpr any_node<N> const nary_expr_     = {};
  template<typename Tag, typename... Children> struct node;

  // Overload for unary node
  template<typename Tag, typename Child> struct node<Tag, Child> : expr<node<Tag, Child>>
  {
    constexpr explicit node(Child const& c) noexcept : child0_(c) {}

    static constexpr int arity() noexcept { return 1;  }
    static constexpr Tag  tag()  noexcept { return {}; }
    static constexpr bool is_placeholder()   noexcept { return false; }

    constexpr void value() const noexcept =delete;

    template<std::size_t Index> constexpr Child get() const noexcept
    {
      static_assert(Index == 0, "Invalid child access");
      return child0_;
    }

    static constexpr bool match(type_t<any_expr>) noexcept { return true; }

    template<typename OTag, typename OChild>
    static constexpr bool match(type_t<node<OTag, OChild>>) noexcept
    {
      return std::is_same_v<Tag,OTag> && Child::match( type_t<OChild>{} );
    }

    template<typename Other> static constexpr bool match(type_t<Other>) noexcept
    {
      return std::is_same_v<Other,any_node<1>>;
    }

    private:
    Child child0_;
  };

  // Overload for binary node
  template<typename Tag, typename Child0, typename Child1>
  struct node<Tag, Child0, Child1> : expr<node<Tag, Child0, Child1>>
  {
    constexpr node(Child0 const& c0, Child1 const& c1) : child0_(c0), child1_(c1) {}

    static constexpr int  arity() noexcept { return 2;  }
    static constexpr Tag  tag()   noexcept { return {}; }
    static constexpr bool is_placeholder()   noexcept { return false; }

    constexpr void value() const noexcept =delete;

    template<std::size_t Index>
    constexpr auto get() const noexcept
    {
      static_assert(Index < 2, "Invalid child access");
      if constexpr( Index == 0) return child0_;
      if constexpr( Index == 1) return child1_;
    }

    static constexpr bool match(type_t<any_expr>) noexcept { return true; }

    template<typename Other> static constexpr bool match(type_t<Other>) noexcept
    {
      return std::is_same_v<Other,any_node<2>>;
    }

    template<typename OTag, typename OChild0, typename OChild1>
    static constexpr bool match(type_t<node<OTag, OChild0, OChild1>>) noexcept
    {
      return std::is_same_v<Tag,OTag> && Child0::match( type_t<OChild0>{} )
                                      && Child1::match( type_t<OChild1>{} );
    }

    private:
    Child0 child0_;
    Child1 child1_;
  };

  // Basic case
  template<typename Tag, typename... Children>
  struct node : expr<node<Tag, Children...>>
  {
    constexpr node(Children const&... cs) : children_(cs...) {}

    static constexpr int arity()     noexcept { return sizeof...(Children);  }
    static constexpr Tag tag()       noexcept { return {}; }
    static constexpr bool is_placeholder()   noexcept { return false; }

    constexpr std::tuple<Children...> const& children()  noexcept { return children_; }

    constexpr void value() const noexcept =delete;

    template<std::size_t Index>
    constexpr auto get() const noexcept
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

    static constexpr bool match(type_t<any_expr>) noexcept
    {
      return true;
    }

    template<typename Other> static constexpr bool match(type_t<Other>) noexcept
    {
      return std::is_same_v<Other,any_node<arity()>>;
    }

    template<typename OTag, typename... OChildren>
    static constexpr bool match(type_t<node<OTag, OChildren...>>) noexcept
    {
      return      std::is_same_v<Tag,OTag>
              &&  (sizeof...(Children) == sizeof...(OChildren))
              &&  ( (Children::match( type_t<OChildren>{} ) && ...)  );
    }

    private:
    std::tuple<Children...> children_;
  };
}

#endif
