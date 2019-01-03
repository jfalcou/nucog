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

#include <cstddef>
#include <utility>

namespace nucog
{
  template<typename Tree> struct expr
  {
    // Type detection
    using is_expr_t = void;

    constexpr Tree& self()             noexcept { return static_cast<Tree&>(*this);       }
    constexpr Tree const& self() const noexcept { return static_cast<const Tree&>(*this); }

    static constexpr auto arity() noexcept { return Tree::arity(); }
    static constexpr auto tag()   noexcept { return Tree::tag();   }

    template<std::size_t Index> constexpr decltype(auto) child() const noexcept
    {
      return self().template child<Index>();
    }

    template<std::size_t Index> constexpr decltype(auto) child() noexcept
    {
      return self().template child<Index>();
    }
  };
}

#endif
