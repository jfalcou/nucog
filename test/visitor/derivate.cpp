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
    using nucog::match;
    using nucog::as_expr;
    using nucog::constant;

    constexpr Expression  expr{};
    constexpr Var         var{};

          if constexpr(match(term_, expr))         return as_expr(constant<match(var,expr)>);
    else  if constexpr(match(expr_ + expr_, expr)) return visit(f[0_c]) + visit(f[1_c]);
    else  if constexpr(match(expr_ - expr_, expr)) return visit(f[0_c]) - visit(f[1_c]);
    else  if constexpr(match(expr_ * expr_, expr)) return visit(f[0_c])*f[1_c]+f[0_c]*visit(f[1_c]);
    else  return f;
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

  TTS_EXPECT( derivate(x_ , x_).match(nucog::constant<1>) );
  TTS_EXPECT( derivate(y_ , x_).match(nucog::constant<0>) );
  TTS_EXPECT( derivate(x_ , y_).match(nucog::constant<0>) );
  TTS_EXPECT( derivate(4  , x_).match(nucog::constant<0>) );
  TTS_EXPECT( derivate(4_c, x_).match(nucog::constant<0>) );

  TTS_EXPECT( derivate(x_ + x_, x_).match(nucog::constant<2>) );

  std::cout << derivate(x_ + x_, x_) << "\n";
  std::cout << (3*x_ + 4*x_) << "\n";
  std::cout << (3*x_ + x_) << "\n";
  std::cout << (3*x_ + x_ + x_ + x_ * 3) << "\n";
  std::cout << (x_*2 + x_*7) << "\n";
  std::cout << (x_   + x_*7) << "\n";
  std::cout << (3*x_ + 4*x_) + (x_*2 + x_*7) << "\n";
  std::cout << (x_ + 0_c) << "\n";
  std::cout << (0_c + x_) << "\n";

/*
  std::cout << "d(x*x)/dx\n";
  {
    using namespace nucog::literals;

    auto d = derivate(x_ * x_, x_);
    TTS_EQUAL(d(x_ = 4.5f), 9.f);
  }

  std::cout << "d(x*x*x)/dx2\n";
  {
    using namespace nucog::literals;

    auto d = derivate<2>(x_ * x_ * x_, x_);
    TTS_ULP_EQUAL(d(x_ = 11.1f), 66.6f, 0.5);
  }
*/
};
