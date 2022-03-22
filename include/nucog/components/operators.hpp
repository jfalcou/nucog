//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/traits/supports_overload.hpp>
#include <nucog/components/as_expr.hpp>
#include <nucog/components/expr.hpp>
#include <nucog/components/node.hpp>
#include <nucog/components/tag.hpp>
#include <nucog/traits/match.hpp>
#include <nucog/traits/make.hpp>

namespace nucog::tags
{
  struct unary_plus_  : tag<unary_plus_>  {};
  struct unary_minus_ : tag<unary_minus_> {};
  struct plus_        : tag<plus_>        {};
  struct minus_       : tag<minus_>       {};
  struct multiplies_  : tag<multiplies_>  {};
  struct divides_     : tag<divides_>     {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Operator injections
  template<typename Arg> constexpr auto operator+( expr<Arg> const& arg ) noexcept
  {
    return node{tags::unary_plus_{},arg.self()};
  }
  template<typename Arg> constexpr auto operator-( expr<Arg> const& arg ) noexcept
  {
    return node{tags::unary_minus_{},arg.self()};
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  constexpr auto operator+( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::plus_{}, as_expr(lhs), as_expr(rhs)};
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  constexpr auto operator-( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::minus_{}, as_expr(lhs), as_expr(rhs)};
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  constexpr auto operator*( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::multiplies_{},as_expr(lhs), as_expr(rhs)};
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  constexpr auto operator/( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::divides_{},as_expr(lhs), as_expr(rhs)};
  }

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  constexpr auto evaluate(tags::unary_plus_   const&, auto&& a) { return  a; }
  constexpr auto evaluate(tags::unary_minus_  const&, auto&& a) { return -a; }

  constexpr auto evaluate(tags::plus_       const&, auto&& a, auto&& b) { return a+b; }
  constexpr auto evaluate(tags::minus_      const&, auto&& a, auto&& b) { return a-b; }
  constexpr auto evaluate(tags::multiplies_ const&, auto&& a, auto&& b) { return a*b; }
  constexpr auto evaluate(tags::divides_    const&, auto&& a, auto&& b) { return a/b; }

  // -----------------------------------------------------------------------------------------------
  // Display support
  constexpr auto& display(std::ostream& os, tags::unary_plus_ const&, auto a)
  {
    return os << "+(" << a << ")";
  }

  constexpr auto& display(std::ostream& os, tags::unary_minus_ const&, auto a)
  {
    return os << "-(" << a << ")";
  }

  constexpr auto& display(std::ostream& os, tags::plus_ const&, auto a, auto b)
  {
    return os << a << " + " << b;
  }

  constexpr auto& display(std::ostream& os, tags::minus_  const&, auto a, auto b)
  {
    return os << a << " - " << b;
  }

  constexpr auto& display(std::ostream& os, tags::multiplies_ const&, auto a, auto b)
  {
    return os << a << " * " << b;
  }

  constexpr auto& display(std::ostream& os, tags::divides_ const&, auto a, auto b)
  {
    return os << a << " / " << b;
  }
}
