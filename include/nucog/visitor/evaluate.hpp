//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace nucog::tags
{
  struct terminal_;
}

namespace nucog
{
  template<typename Environment>
  struct evaluate_visitor
  {
    constexpr evaluate_visitor(Environment const& e) : env_(e) {}

    template<typename Expression>
    constexpr auto visit(Expression const& expr)
    {
      if constexpr(Expression::arity() == 0)
      {
        return evaluate( env_, Expression::tag(), expr.value() );
      }
      else
      {
        return  [&]<std::size_t... I>( std::index_sequence<I...>) -> decltype(auto)
                {
                  return evaluate( env_, Expression::tag(), expr[literal::idx_<I>{}]... );
                }( std::make_index_sequence<Expression::arity()>{} );
      }
    }

    constexpr Environment const& env() { return env_; }

    private:
    Environment const& env_;
  };

  template<typename Environment, typename Expression>
  constexpr auto evaluate(Environment const& env, Expression const& expr)
  {
    evaluate_visitor<Environment> v{env};
    return v.visit(expr);
  }

  template<typename Environment, typename Tag, typename... Cs>
  constexpr auto evaluate(Environment const& env, Tag const& tag, Cs const&... cs)
  {
    evaluate_visitor<Environment> ev{env};
    return evaluate(tag, ev.visit(cs)...);
  }
}
