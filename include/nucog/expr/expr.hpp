//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <nucog/literal.hpp>
#include <nucog/detail/helpers.hpp>
#include <nucog/detail/raberu.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/visitor/evaluate.hpp>
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

    template<typename Other> static constexpr bool match(type_t<expr<Other>>) noexcept
    {
      return Tree::match(type_t<Other>{});
    }

    template<typename Other> static constexpr bool match(type_t<Other> t) noexcept
    {
      return Tree::match(t);
    }

    template<std::size_t Index>
    constexpr auto operator[]( literal::idx_<Index> const&) const noexcept
    {
      return self().template get<Index>();
    }

    template<typename... Params>
    constexpr auto operator()(Params const&... ps) const
    {
      return evaluate( rbr::settings(ps...), *this );
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
