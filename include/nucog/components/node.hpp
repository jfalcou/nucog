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
  template<typename Tag, typename... Children>
  struct node : expr<node<Tag, Children...>>
  {
    constexpr node(Children const&... cs) : children_{cs...} {}

    static constexpr int  arity()           noexcept { return sizeof...(Children);  }
    static constexpr Tag  tag()             noexcept { return {}; }
    static constexpr bool is_placeholder()  noexcept { return false; }

    constexpr kumi::tuple<Children...> const& children()  noexcept { return children_; }

    template<std::size_t Index> constexpr auto get() const noexcept
    {
      if constexpr(Index < arity()) return get<Index>(children_);
      else
      {
        static_assert(Index < arity(), "Invalid child access");
        return *this;
      }
    }

    static constexpr bool match(type_t<any_expr>) noexcept { return true; }

/*
    template<typename OtherTag>
    static constexpr bool match(type_t<tag_node<OtherTag>>) noexcept
    {
      return std::is_same_v<Tag,OTag>;
    }

    template<typename Other> static constexpr bool match(type_t<Other>) noexcept
    {
      return std::is_same_v<Other,any_node<arity()>>;
    }

    template<typename OtherTag, typename... OtherChildren>
    static constexpr bool match(type_t<node<OtherTag, OtherChildren...>>) noexcept
    {
      return      std::is_same_v<Tag,OtherTag>
              &&  (sizeof...(Children) == sizeof...(OtherChildren))
              &&  ( (Children::match( type_t<OtherChildren>{} ) && ...)  );
    }
*/

    private:
    kumi::tuple<Children...> children_;
  };
}
