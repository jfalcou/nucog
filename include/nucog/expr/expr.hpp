//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_EXPR_HPP_INCLUDED
#define NUCOG_EXPR_EXPR_HPP_INCLUDED

#include <nucog/literal.hpp>
#include <nucog/detail/helpers.hpp>
#include <nucog/expr/tag.hpp>
#include <cstddef>
#include <utility>

namespace nucog
{
  //================================================================================================
  // Expression wrapper
  template<typename Tree> struct expr
  {
    constexpr Tree& self()             noexcept { return static_cast<Tree&>(*this);       }
    constexpr Tree const& self() const noexcept { return static_cast<const Tree&>(*this); }

    static constexpr auto arity()           noexcept { return Tree::arity(); }
    static constexpr auto tag()             noexcept { return Tree::tag();   }
    static constexpr bool is_placeholder()  noexcept { return Tree::is_placeholder(); }

    constexpr auto value() const noexcept { return self().value(); }

    template<typename Other> static constexpr bool match(type_<expr<Other>>) noexcept
    {
      return Tree::match(type_<Other>{});
    }

    template<typename Other> static constexpr bool match(type_<Other> t) noexcept
    {
      return Tree::match(t);
    }

    template<std::size_t Index>
    constexpr auto operator[]( literal::idx_<Index> const&) const noexcept
    {
      return self().template get<Index>();
    }
  };

  //================================================================================================
  // Joker for any expr in matcher
  struct any_expr : expr<any_expr>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_expr const expr_ = {};
}

#endif
