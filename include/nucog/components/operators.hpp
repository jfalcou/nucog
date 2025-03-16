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
#include <cmath>

namespace nucog::tags
{
  struct unary_plus_  : tag<unary_plus_>  {};
  struct unary_minus_ : tag<unary_minus_> {};
  struct plus_        : tag<plus_>        {};
  struct minus_       : tag<minus_>       {};
  struct multiplies_  : tag<multiplies_>  {};
  struct divides_     : tag<divides_>     {};
  struct power_       : tag<power_>       {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Unary Operators
  template<typename Arg>
  NUCOG_FORCEINLINE constexpr auto operator+( expr<Arg> const& arg ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename A>(A const& a)
    {
      using namespace nucog::literals;
      constexpr tags::unary_plus_ op = {};

      //--- Placeholders don't get simplified
      if        constexpr ( A::is_placeholder() )                 return node{op,a};
      //--- +(+x) is x
      else  if  constexpr ( A::match(node_<tags::unary_plus_>) )  return a;
      //--- +(-x) is -x
      else  if  constexpr ( A::match(node_<tags::unary_minus_>) ) return a;
      //--- No simplification found
      else                                                        return node{op,a};
    };

    return build(arg.self());
  }

  template<typename Arg>
  NUCOG_FORCEINLINE constexpr auto operator-( expr<Arg> const& arg ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename A>(A const& a)
    {
      using namespace nucog::literals;
      constexpr tags::unary_minus_ op = {};

      //--- Placeholders don't get simplified
      if        constexpr ( A::is_placeholder() )                   return node{op,a};
      //--- -(-x) is x
      else  if  constexpr ( A::match(node_<tags::unary_minus_>) )   return a[0_c];
      //--- -(+x) is -x
      else  if  constexpr ( A::match(node_<tags::unary_plus_>) )    return node{op,a[0_c]};
      //--- No simplification found
      else                                                          return node{op,a};
    };

    return build(arg.self());
  }

  // -----------------------------------------------------------------------------------------------
  // Binary Operators
  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator^( LHS const& lhs, RHS const& rhs ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename L, typename R>(L const& l, R const& r)
    {
      using namespace nucog::literals;
      constexpr tags::power_ op = {};

      //--- Placeholders don't get simplified
      if          constexpr( L::is_placeholder() || R::is_placeholder() )  return node{op,l,r};
      //--- x^0 is 1
      else  if  constexpr ( R::match(0_c) )         return as_expr(1_c);
      //--- x^1 is x
      else  if  constexpr ( R::match(1_c) )         return l;
      //--- x^N^M is x^N*M
      else  if  constexpr ( L::match(expr_ ^ lit_) && R::match(lit_) )
          return node{op, l[0_c], r[0_c]*l[1_c]};
      //--- No simplification found
      else                                          return node{op, l, r};
    };

    return build(as_expr(lhs), as_expr(rhs));
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator*( LHS const& lhs, RHS const& rhs ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename L, typename R>(L const& l, R const& r)
    {
      using namespace nucog::literals;
      constexpr tags::multiplies_ op = {};

      //--- Placeholders don't get simplified
      if          constexpr( L::is_placeholder() || R::is_placeholder() )  return node{op,l,r};
      //--- 1 is identity for *
      else  if  constexpr ( L::match(1_c) ) return r;
      else  if  constexpr ( R::match(1_c) ) return l;
      //--- 0 is absorbing for *
      else  if  constexpr ( L::match(0_c) ) return as_expr(0_c);
      else  if  constexpr ( R::match(0_c) ) return as_expr(0_c);
      //--- normalize expr * lit_ to lit_ * expr
      else  if  constexpr ( R::match(lit_) && !L::match(lit_)) return r*l;
      //--- x * pow(x,N) is pow(x, N+1)
      else  if  constexpr ( R::match(expr_ ^ lit_) && L::match(R{}[0_c]) )
            return node{tags::power_{}, l, as_expr(1_c + r[1_c])};
      //--- pow(x,N) * x is pow(x, N+1)
      else  if  constexpr ( L::match(expr_ ^ lit_) && R::match(L{}[0_c]) )
            return node{tags::power_{}, r, as_expr(1_c + l[1_c])};
      //--- pow(x,N) * pow(x,M) is pow(x, N+M)
      else  if  constexpr ( L::match(expr_ ^ lit_) && R::match(expr_ ^ lit_)
                          && match(L{}[0_c], R{}[0_c]) )
            return node{tags::power_{}, l[0_c], as_expr(r[1_c] + l[1_c])};
      //--- x * x is pow(x, 2_c)
      else  if  constexpr ( L::match(R{}) ) return node{tags::power_{}, l, as_expr(2_c)};
      //--- compact literals
      else  if  constexpr ( L::match(lit_ * expr_) && R::match(lit_ * expr_) )
        return as_expr(l[0_c].value() * r[0_c].value()) * (l[1_c]*r[1_c]);
      else  if  constexpr ( L::match(lit_) && R::match(lit_ * expr_) )
        return as_expr(l.value() * r[0_c]) * r[1_c];
      else  if  constexpr ( R::match(lit_) && L::match(lit_ * expr_) )
        return as_expr(r.value() * l[0_c]) * l[1_c];
      else  if  constexpr ( matches(lit_, L{}, R{}) )
        return as_expr(l.value() * r.value());
      //--- No simplification found
      else                                          return node{op, l, r};
    };

    return build(as_expr(lhs), as_expr(rhs));
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
      if       constexpr( L::is_placeholder() || R::is_placeholder() )  return node{op,l,r};
      //--- 0 is identity for +
      else  if constexpr( L::match(0_c) ) return r;
      else  if constexpr( R::match(0_c) ) return l;
      //--- normalize expr + lit_ to lit_ + expr
      else  if  constexpr ( R::match(lit_) && !L::match(lit_)) return r+l;
      //--- compact literals
      else  if  constexpr ( L::match(lit_ + expr_) && R::match(lit_ + expr_) )
        return as_expr(l[0_c].value() + r[0_c].value()) + r[1_c];
      else  if  constexpr ( L::match(lit_ * expr_) && R::match(lit_ * expr_) )
        return as_expr(l[0_c].value() + r[0_c].value()) * r[1_c];
      else  if  constexpr ( L::match(lit_ * expr_) && R::match(L{}[1_c]) )
        return as_expr(l[0_c].value() + 1_c) * r[1_c];
      else  if  constexpr ( R::match(lit_ * expr_) && L::match(R{}[1_c]) )
        return as_expr(r[ 0_c].value() + 1_c) * l[1_c];
      else  if  constexpr ( L::match(lit_) && R::match(lit_ * expr_) )
        return as_expr(l.value() + r[0_c].value()) * r[1_c];
      else  if  constexpr ( R::match(lit_) && L::match(lit_ * expr_) )
        return as_expr(r.value() + l[0_c].value()) * l[1_c];
      else  if  constexpr ( L::match(lit_) && R::match(lit_ + expr_) )
        return as_expr(l.value() + r[0_c].value()) + r[1_c];
      else  if  constexpr ( R::match(lit_) && L::match(lit_ + expr_) )
        return as_expr(r.value() + l[0_c].value()) + l[1_c];
      else  if  constexpr ( matches(lit_, L{}, R{}) )
        return as_expr(l.value() + r.value());
      else  if constexpr( L::match(R{}) )
        return 2_c * l;
      //--- No simplification found
      else                                          return node{op, l, r};
    };

    return build(as_expr(lhs), as_expr(rhs));
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator-( LHS const& lhs, RHS const& rhs ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename L, typename R>(L const& l, R const& r)
    {
      using namespace nucog::literals;
      constexpr tags::minus_ op = {};

      //--- Placeholders don't get simplified
      if       constexpr( L::is_placeholder() || R::is_placeholder() )  return node{op,l,r};
      //--- 0 is almost identify for -
      else  if constexpr( L::match(0_c)           ) return  r;
      else  if constexpr( R::match(0_c)           ) return -l;
      //--- compact literals
      else  if constexpr( matches(lit_, L{}, R{}) ) return as_expr(l.value() - r.value());
      //--- Handle all permutation of (lit * expr)/(expr * lit)/lit sum
      else  if constexpr( L::match(R{}) )           return as_expr(0_c);
      else  if constexpr( matches(lit_ * expr_,L{},R{}) && L{}[1_c].match(R{}[1_c]) )
                                                    return (l[0_c].value()-r[0_c].value()) * l[1_c];
      else  if constexpr( matches(expr_ * lit_,L{},R{}) && L{}[0_c].match(R{}[0_c]) )
                                                    return (l[1_c].value()-r[1_c].value()) * l[0_c];
      else  if constexpr(   L::match(expr_ * lit_) && R::match(lit_ * expr_)
                        &&  L{}[0_c].match(R{}[1_c])
                        )
                                                    return (l[1_c].value()-r[0_c].value()) * l[0_c];
      else  if constexpr(   L::match(lit_ * expr_) && R::match(expr_ * lit_)
                        &&  L{}[1_c].match(R{}[0_c])
                        )
                                                    return (l[0_c].value()-r[1_c].value()) * l[1_c];
      else  if constexpr( L::match(expr_ * lit_) && R::match(L{}[0_c]) )
                                                    return (l[1_c].value()-1_c) * l[0_c];
      else  if constexpr( R::match(expr_ * lit_) && L::match(R{}[0_c]) )
                                                    return (r[1_c].value()-1_c) * r[0_c];
      else  if constexpr( L::match(lit_ * expr_) && R::match(L{}[1_c]) )
                                                    return (l[0_c].value()-1_c) * l[1_c];
      else  if constexpr( R::match(lit_ * expr_) && L::match(R{}[1_c]) )
                                                    return (r[0_c].value()-1_c) * r[1_c];
      //--- No simplification found
      else                                          return node{op, l, r};
    };

    return build(as_expr(lhs), as_expr(rhs));
  }

  template<typename LHS, typename RHS>
  requires support_overload<LHS,RHS>
  NUCOG_FORCEINLINE constexpr auto operator/( LHS const& lhs, RHS const& rhs ) noexcept
  {
    // Apply safe simplification
    auto build = []<typename L, typename R>(L const& l, R const& r)
    {
      using namespace nucog::literals;
      constexpr tags::divides_ op = {};

      //--- Placeholders don't get simplified
      if          constexpr( L::is_placeholder() || R::is_placeholder() )  return node{op,l,r};
      //--- x/1 is identity for x
      else  if  constexpr ( R::match(1_c) ) return l;
      //--- 1/x is pow(x,-1)
      else  if  constexpr ( L::match(1_c) ) return node{tags::power_{}, r, -as_expr(1_c) };
      //--- No simplification found
      else                                  return node{op, l, r};
    };

    return build(as_expr(lhs), as_expr(rhs));
  }

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  NUCOG_FORCEINLINE constexpr auto eval(tags::unary_plus_   const&, auto&& a) { return  a; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::unary_minus_  const&, auto&& a) { return -a; }

  NUCOG_FORCEINLINE constexpr auto eval(tags::plus_       const&, auto&& a, auto&& b) { return a+b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::minus_      const&, auto&& a, auto&& b) { return a-b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::multiplies_ const&, auto&& a, auto&& b) { return a*b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::divides_    const&, auto&& a, auto&& b) { return a/b; }
  NUCOG_FORCEINLINE constexpr auto eval(tags::power_      const&, auto&& a, auto&& b)
  {
    return std::pow(a,b);
  }

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

  constexpr auto& display(std::ostream& os, tags::power_ const&, auto a, auto b)
  {
    return os << a << " ^ " << b;
  }
}
