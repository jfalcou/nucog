//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/components/literal.hpp>
#include <nucog/traits/default_evaluator.hpp>

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

    constexpr auto value()    const noexcept { return self().value();     }
    constexpr auto children() const noexcept { return self().children();  }

    static constexpr auto tree()     noexcept { return Tree();  }

    template<typename U> static constexpr bool match(U t) noexcept { return Tree::match(t); }

    template<std::size_t Index>
    constexpr decltype(auto) operator[]( index_t<Index> const&) const noexcept
    {
      return self().template get<Index>();
    }

    template<rbr::concepts::option... Params>
    NUCOG_FORCEINLINE constexpr auto operator()(Params const&... ps) const
    {
      using evaluator_t = typename default_evaluator<typename Params::stored_value_type...>::type;
      return evaluator_t{}.accept( rbr::settings(ps...), *this );
    }

    template<expr_evaluator Context, rbr::concepts::option... Params>
    NUCOG_FORCEINLINE constexpr auto operator()(Context const& ctx, Params const&... ps) const
    {
      return ctx.accept( rbr::settings(ps...), *this );
    }

    friend std::ostream& operator<<(std::ostream& os, expr const& e) { return os << e.self(); }
  };

  //================================================================================================
  // Joker for any expr in matcher
  struct any_expr : expr<any_expr>
  {
    static constexpr bool is_placeholder()  noexcept { return true; }
  };

  inline constexpr any_expr const expr_ = {};
}
