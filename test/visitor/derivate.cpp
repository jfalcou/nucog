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
  template<typename Expression> constexpr auto visit(Expression const& formula) const
  {
    using namespace nucog::literal;
    using nucog::term_;
    using nucog::expr_;
    using nucog::match;
    using nucog::as_expr;

    constexpr Expression  expr{};
    constexpr Var         var{};

    //==============================================================================================
    // d(term)/d(var) is 1 if term === var
    if constexpr( match(expr,term_) )
    {
      return as_expr(nucog::constant<match(expr,var)>);
    }
    //==============================================================================================
    // d(expr+expr)/d(var)
    else if constexpr( match(expr,expr_ + expr_ ) )
    {
      auto lhs = formula[0_c];
      auto rhs = formula[1_c];
      return simplify(visit(simplify(lhs)) + visit(simplify(rhs)));
    }
    //==============================================================================================
    // d(expr-expr)/d(var)
    else if constexpr( match(expr,expr_ - expr_ ) )
    {
      auto lhs = formula[0_c];
      auto rhs = formula[1_c];
      return simplify(visit(simplify(lhs)) - visit(simplify(rhs)));
    }
    //==============================================================================================
    // d(expr*expr)/d(var)
    else if constexpr( match(expr,expr_ * expr_ ) )
    {
      auto lhs = formula[0_c];
      auto rhs = formula[1_c];

      return simplify( simplify(visit(lhs)*rhs) + simplify(lhs*visit(rhs)) );
    }
    else return formula;
  }

  template<typename Expression>
  static constexpr auto simplify(Expression const& formula)
  {
    using namespace nucog::literal;
    using nucog::term_;
    using nucog::expr_;
    using nucog::lit_;
    using nucog::match;
    using nucog::as_expr;

    constexpr auto expr = Expression{};
    constexpr auto tree = expr.tree();

    //==============================================================================================
    // Simplify expr + expr tree
    if constexpr( match(expr,expr_ + expr_ ) )
    {
            if  constexpr( match(tree,0_c   + expr_ ) ) return simplify(formula[1_c]);
      else  if  constexpr( match(tree,expr_ + 0_c   ) ) return simplify(formula[0_c]);
      else  if  constexpr (   match(tree,lit_ * expr_ + lit_ * expr_)
                          &&  match(tree[0_c][1_c],tree[1_c][1_c])
                          )
      {
          return simplify( (formula[0_c][0_c].value()+formula[1_c][0_c].value()) * formula[1_c][1_c]);
      }
      else  if  constexpr (   match(tree,lit_ * expr_ + expr_)
                          &&  match(tree[0_c][1_c],tree[1_c])
                          )
      {
        return (formula[0_c][0_c].value()+1_c) * simplify(formula[1_c]);
      }
      else  if  constexpr (   match(tree,expr_ + lit_ * expr_)
                          &&  match(tree[0_c],tree[1_c][1_c])
                          )
      {
        return (formula[1_c][0_c].value()+1_c) * simplify(formula[0_c]);
      }
      else
      {
        return simplify(formula[0_c]) + simplify(formula[1_c]);
      }
    }
    else if constexpr( match(expr,expr_ * expr_ ) )
    {
      constexpr auto lhs = tree[0_c];
      constexpr auto rhs = tree[1_c];

            if constexpr(match(lhs,1_c))  return simplify(formula[1_c]);
      else  if constexpr(match(rhs,1_c))  return simplify(formula[0_c]);
      else  if constexpr(match(lhs,0_c))  return nucog::as_expr(0_c);
      else  if constexpr(match(rhs,0_c))  return nucog::as_expr(0_c);
      else  if constexpr(match(lhs,lit_) && match(rhs,lit_))
      {
        return nucog::as_expr(formula[0_c].value()*formula[1_c].value());
      }
      else
      {
        return simplify(formula[0_c]) * simplify(formula[1_c]);
      }
    }
    //==============================================================================================
    // If not, just return expr
    else
    {
      return formula;
    }
  }
};

template<typename Expression, typename Variable>
constexpr auto derivate(Expression const& expr, Variable const& var)
{
  return nucog::as_expr(expr)( derivator{var} );
}

TTS_CASE( "Check derivation formula for:" )
{
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;
  using nucog::index;

  TTS_EXPECT( derivate(x_ , x_).match(nucog::constant<1>) );
  TTS_EXPECT( derivate(y_ , x_).match(nucog::constant<0>) );
  TTS_EXPECT( derivate(x_ , y_).match(nucog::constant<0>) );
  TTS_EXPECT( derivate(4  , x_).match(nucog::constant<0>) );
  TTS_EXPECT( derivate(4_c, x_).match(nucog::constant<0>) );

  TTS_EXPECT( derivate(x_ + x_, x_).match(nucog::constant<2>) );

  std::cout << derivate((3*x_ + x_) *(7*x_+x_), x_) << "\n";

/*
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
};
