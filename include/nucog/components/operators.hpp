//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/traits/support_overload.hpp>
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
  template<typename Arg>
  NUCOG_FORCEINLINE constexpr auto operator+( expr<Arg> const& arg ) noexcept
  {
    return node{tags::unary_plus_{},arg.self()};
  }
  template<typename Arg>
  NUCOG_FORCEINLINE constexpr auto operator-( expr<Arg> const& arg ) noexcept
  {
    return node{tags::unary_minus_{},arg.self()};
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator*( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::multiplies_{},as_expr(lhs), as_expr(rhs)};
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator+( LHS const& lhs, RHS const& rhs ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename L, typename R>(L const& l, R const& r)
    {
      using namespace nucog::literals;
      constexpr tags::plus_ op = {};

      //--- Placeholders don't get simplified
            if constexpr( L::is_placeholder() || R::is_placeholder() )  return node{op,l,r};
      //--- 0 is identity for +
      else  if constexpr( L::match(0_c)           ) return r;
      else  if constexpr( R::match(0_c)           ) return l;
      //--- compact literals
      else  if constexpr( matches(lit_, L{}, R{}) ) return as_expr(l.value() + r.value());
      //--- Handle all permutation of (lit * expr)/(expr * lit)/lit sum
      else  if constexpr( matches(lit_ * expr_,L{},R{}) && L{}[1_c].match(R{}[1_c]) )
                                                    return (l[0_c].value()+r[0_c].value()) * l[1_c];
      else  if constexpr( matches(expr_ * lit_,L{},R{}) && L{}[0_c].match(R{}[0_c]) )
                                                    return (l[1_c].value()+r[1_c].value()) * l[0_c];
      else  if constexpr(   L::match(expr_ * lit_) && R::match(lit_ * expr_)
                        &&  L{}[0_c].match(R{}[1_c])
                        )
                                                    return (l[1_c].value()+r[0_c].value()) * l[0_c];
      else  if constexpr(   L::match(lit_ * expr_) && R::match(expr_ * lit_)
                        &&  L{}[1_c].match(R{}[0_c])
                        )
                                                    return (l[0_c].value()+r[1_c].value()) * l[1_c];
      else  if constexpr( L::match(expr_ * lit_) && R::match(L{}[0_c]) )
                                                    return (l[1_c].value()+1_c) * l[0_c];
      else  if constexpr( R::match(expr_ * lit_) && L::match(R{}[0_c]) )
                                                    return (r[1_c].value()+1_c) * r[0_c];
      else  if constexpr( L::match(lit_ * expr_) && R::match(L{}[1_c]) )
                                                    return (l[0_c].value()+1_c) * l[1_c];
      else  if constexpr( R::match(lit_ * expr_) && L::match(R{}[1_c]) )
                                                    return (r[0_c].value()+1_c) * r[1_c];
      //--- No simplification found
      else                                          return node{op, l, r};
    };

    return build(as_expr(lhs), as_expr(rhs));
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator-( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::minus_{}, as_expr(lhs), as_expr(rhs)};
  }


  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator/( LHS const& lhs, RHS const& rhs ) noexcept
  {
    return node{tags::divides_{},as_expr(lhs), as_expr(rhs)};
  }

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  NUCOG_FORCEINLINE constexpr auto eval(tags::unary_plus_   const&, auto&& a) { return  a; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::unary_minus_  const&, auto&& a) { return -a; }

  NUCOG_FORCEINLINE constexpr auto eval(tags::plus_       const&, auto&& a, auto&& b) { return a+b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::minus_      const&, auto&& a, auto&& b) { return a-b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::multiplies_ const&, auto&& a, auto&& b) { return a*b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::divides_    const&, auto&& a, auto&& b) { return a/b; }

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
