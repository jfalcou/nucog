//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/components/expr.hpp>

namespace nucog
{
  //================================================================================================
  // Joker for any node in matcher
  template<int Arity> struct any_node : expr<any_node<Arity>>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  template<typename Tag> struct tag_node : expr<tag_node<Tag>>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_node<1> const unary_expr_    = {};
  inline constexpr any_node<2> const binary_expr_   = {};
  inline constexpr any_node<3> const ternary_expr_  = {};

  template<typename Tag> inline constexpr tag_node<Tag> const node_ = {};

  template<int N>
  inline constexpr any_node<N> const nary_expr_     = {};
  template<typename Tag, typename... Children> struct node;

  template<typename Tag, typename... Children>
  struct node : expr<node<Tag, Children...>>
  {
    constexpr node() {}
    constexpr node(Tag const&, Children const&... cs) : children_{cs...} {}

    static constexpr auto arity()           noexcept { return sizeof...(Children);  }
    static constexpr Tag  tag()             noexcept { return {}; }
    static constexpr bool is_placeholder()  noexcept { return false; }

    constexpr kumi::tuple<Children...> const& children() const noexcept { return children_; }

    template<std::size_t Index> constexpr auto get() const noexcept
    {
      if constexpr(Index < arity()) return kumi::get<Index>(children_);
      else
      {
        static_assert(Index < arity(), "Invalid child access");
        return *this;
      }
    }

    static constexpr bool match(any_expr) noexcept { return true; }

    template<typename OtherTag>
    static constexpr bool match(tag_node<OtherTag>) noexcept
    {
      return std::is_same_v<Tag,OtherTag>;
    }

    template<typename Other> static constexpr bool match(Other) noexcept
    {
      return std::is_same_v<Other,any_node<arity()>>;
    }

    template<typename OtherTag, typename... Others>
    static constexpr bool match(node<OtherTag, Others...> const&) noexcept
    {
            if constexpr( sizeof...(Children) != sizeof...(Others) )  return false;
      else  if constexpr( !std::is_same_v<Tag,OtherTag> )             return false;
      else                             return (Children::match( Others{} ) && ...);
    }

    friend std::ostream& operator<<(std::ostream& os, node const& n)
    {
      if constexpr( node::arity() == 1 )
      {
        display(os, Tag{}, n.get<0>() );
        return os;
      }
      else
      {
        os << "(";
        kumi::apply( [&](auto const&... m) { display(os, Tag{},m...); }, n.children() );
        return os << ")";
      }
    }

    private:
    kumi::tuple<Children...> children_;
  };
}
