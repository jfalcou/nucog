//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>

//==================================================================================================
// Evaluates a nucog::expression to reconstruct its derivative
template<typename Var> struct derivator
{
  using nucog_evaluator = void;

  constexpr derivator(Var const&) {}

  //================================================================================================
  // Accept to visit the expression
  template<typename... Opts, typename Expression>
  constexpr auto accept(rbr::settings<Opts...> const&, Expression const& expr) const
  {
    return visit( expr );
  }

  //================================================================================================
  // Visit try to match known structure to apply derivative on them
  template<typename Expression> constexpr auto visit(Expression const& f) const
  {
    using namespace nucog::literals;
    using nucog::term_;
    using nucog::expr_;
    using nucog::lit_;
    using nucog::match;
    using nucog::as_expr;
    using nucog::constant;

    constexpr Expression  expr{};
    constexpr Var         var{};

    if      constexpr(match(term_, expr)        ) return as_expr(constant<match(var,expr)>);
    else if constexpr(match(expr_ + expr_, expr)) return visit(f[0_c]) + visit(f[1_c]);
    else if constexpr(match(expr_ - expr_, expr)) return visit(f[0_c]) - visit(f[1_c]);
    else if constexpr(match(expr_ * expr_, expr)) return visit(f[0_c])*f[1_c]+f[0_c]*visit(f[1_c]);
    else if constexpr(match(expr_ ^ lit_ , expr)) return (f[1_c]) * (f[0_c] ^ (f[1_c] - 1_c)) * visit(f[0_c]);
    else return f;
  }
};

template<typename Expression, typename Variable>
constexpr auto derivate(Expression const& expr, Variable const& var)
{
  return nucog::as_expr(expr)( derivator{var} );
}

TTS_CASE( "Check derivation formula for:" )
{
  using namespace nucog::literals;
  using nucog::x_;
  using nucog::y_;
  using nucog::index;

  TTS_CONSTEXPR_EXPECT( derivate(x_     , x_).match(nucog::constant<1>) );
  TTS_CONSTEXPR_EXPECT( derivate(y_     , x_).match(nucog::constant<0>) );
  TTS_CONSTEXPR_EXPECT( derivate(x_     , y_).match(nucog::constant<0>) );
  TTS_CONSTEXPR_EXPECT( derivate(4      , x_).match(nucog::constant<0>) );
  TTS_CONSTEXPR_EXPECT( derivate(4_c    , x_).match(nucog::constant<0>) );
  TTS_CONSTEXPR_EXPECT( derivate(x_ + x_, x_).match(nucog::constant<2>) );
  //TTS_EXPECT( derivate(x_ * x_, x_).match(2_c * x_) );

  // std::cout << (x_ + x_) << "\n";
  // std::cout << (1_c / x_) << "\n";
  // std::cout << (x_ + (x_ + x_)) << "\n";
  // std::cout << (x_ + x_ + x_) << "\n";
  // std::cout << (4_c + (x_ + 8_c)) << "\n";
  // std::cout << (x_ + 8_c) << "\n";
  // std::cout << (x_ + 8_c * x_) << "\n";
  // std::cout << (x_ + x_ + x_ + x_) << "\n";
  // std::cout << ((4_c + x_) + (7_c + x_)) << "\n";
  // std::cout << ((x_ + x_) + (x_ + x_)) << "\n";
  // std::cout << ( (x_ ^ 4_c) ^ 3_c) << "\n";
  // std::cout << derivate(x_ + x_ + x_ + x_, x_) << "\n";
  std::cout << (x_*x_*x_ + x_ * 8) << "\n";
  std::cout << derivate(x_*x_*x_ + x_ * 8, x_) << "\n";
//  std::cout << derivate(derivate(x_ + x_ + x_ + x_, x_), x_) << "\n";
  // TTS_EXPECT( derivate(x_ + x_ * x_, x_).match(2_c * x_) );
};
