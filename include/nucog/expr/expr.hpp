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

#include <type_traits>

namespace nucog
{
  template<typename Tree> struct expr
  {
    constexpr Tree& self()             noexcept { return static_cast<Tree&>(*this);       }
    constexpr Tree const& self() const noexcept { return static_cast<const Tree&>(*this); }

    constexpr auto arity()  const noexcept { return self().arity(); }
    constexpr auto tag()    const noexcept { return self().tag();   }

    template<std::size_t Index
            , typename  = std::enable_if_t<(arity() != 0)>
            >
    constexpr decltype(auto) child() const noexcept
    {
      return self().child<Index>();
    }

    template<std::size_t Index
            , typename  = std::enable_if_t<(arity() != 0)>
            >
    constexpr decltype(auto) child() noexcept
    {
      return self().child<Index>();
    }
  };
}

#endif
