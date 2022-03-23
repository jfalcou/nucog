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
template<typename Var>
struct derivator
{
  using nucog_evaluator = void;

  derivator(Var const&) {}

  //================================================================================================
  // Accept to visit the expression
  template<typename... Opts, typename Expression>
  constexpr auto accept(rbr::settings<Opts...> const& env, Expression const&) const
  {
    constexpr auto expr = Expression{};
    constexpr auto var  = Var{};

    if constexpr( nucog::match(expr,nucog::term_) )
    {
      // d(x)/d(y) = 1 iff x iss y
      return nucog::as_expr(nucog::index<nucog::match(expr,var)>);
    }
    else return expr;
  }

  // template<typename Environment, typename Expression>
  // constexpr auto visit(Environment const& env, Expression const& expr) const
  // {
  // }
};

template<typename Expression, typename Variable>
constexpr auto derivate(Expression const& expr, Variable const& var)
{
  return expr( derivator{var} );
}

/*
template<typename Variable>
struct derivate_visitor
{
  constexpr derivate_visitor(Variable const& v) : var_(v) {}

  template<typename Expression>
  constexpr auto visit(Expression const& expr) noexcept
  {
    using namespace nucog::literal;
    using nucog::term_;
    using nucog::expr_;

    if constexpr( NUCOG_MATCH(expr,term_) )
    {
      // d(x)/d(y) = 1 iff x is y
      return nucog::as_expr(nucog::literal::idx_<NUCOG_MATCH(expr,var_)>{});
    }
    else if constexpr( NUCOG_MATCH(expr,expr_ + expr_ ) )
    {
      return visit(expr[0_c]) + visit(expr[1_c]);
    }
    else if constexpr( NUCOG_MATCH(expr, expr_ - expr_ ) )
    {
      return visit(expr[0_c]) - visit(expr[1_c]);
    }
    else if constexpr( NUCOG_MATCH(expr, expr_ * expr_ ) )
    {
      auto const& l = expr[0_c];
      auto const& r = expr[1_c];
      return visit(l)*r + l*visit(r);
    }
  }

  private:
  Variable var_;
};

template<typename Expression, typename Variable>
constexpr auto derivate(Expression const& expr, Variable const& var) noexcept
{
  derivate_visitor<Variable> v{var};
  return v.visit(nucog::as_expr(expr));
}

template<int Degree, typename Expression, typename Variable>
constexpr auto derivate(Expression const& expr, Variable const& var) noexcept
{
  derivate_visitor<Variable> v{var};
  if constexpr(Degree == 1)
  {
    return v.visit(nucog::as_expr(expr));
  }
  else
  {
    return derivate<Degree-1>( v.visit(nucog::as_expr(expr)), var);
  }
}
*/

TTS_CASE( "Check derivation formula for:" )
{
  using nucog::x_;

  std::cout << "dx/dx\n";
  {
    auto d = derivate(x_, x_);
    std::cout << d << "\n";
    //TTS_EQUAL(d(x_ = 4), 1ULL);
  }

/*
  std::cout << "dx/dy\n";
  {
    using nucog::y_;
    auto d = derivate(x_, y_);
    TTS_EQUAL(d(x_ = 4), 0ULL);
  }

  std::cout << "d4/dx\n";
  {
    auto d = derivate(4, x_);
    TTS_EQUAL(d(x_ = 4), 0ULL);
  }

  std::cout << "d4_c/dx\n";
  {
    using namespace nucog::literal;

    auto d = derivate(4_c, x_);
    TTS_EQUAL(d(x_ = 5), 0ULL);
  }

  std::cout << "d(x+x)/dx\n";
  {
    using namespace nucog::literal;

    auto d = derivate(x_ + x_, x_);
    TTS_EQUAL(d(x_ = 3), 2ULL);
  }

  std::cout << "d(x*x)/dx\n";
  {
    using namespace nucog::literal;

    auto d = derivate(x_ * x_, x_);
    TTS_EQUAL(d(x_ = 4.5f), 9.f);
  }

  std::cout << "d(x*x*x)/dx2\n";
  {
    using namespace nucog::literal;

    auto d = derivate<2>(x_ * x_ * x_, x_);
    TTS_ULP_EQUAL(d(x_ = 11.1f), 66.6f, 0.5);
  }
*/
}
