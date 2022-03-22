//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace nucog
{
  template<typename Environment>
  struct evaluator
  {
    evaluator(Environment const& e) : env_(e) {}

    template<typename Expression> constexpr auto visit(Expression const& expr) const
    {
      if constexpr(Expression::arity() == 0)
      {
        return evaluate(env_,Expression::tag(), expr.value());
      }
      else
      {
        return  kumi::apply ( [&](auto const&... cs)
                              {
                                return evaluate(Expression::tag(), visit(cs)...);
                              }
                            , expr.children()
                            );
      }
    }

    constexpr Environment const& env() { return env_; }

    Environment const& env_;
  };

  template<typename Environment, typename Expression>
  constexpr auto evaluate(Environment const& env, Expression const& expr)
  {
    evaluator<Environment> v{env};
    return v.visit(expr);
  }

  template<typename Environment, typename Tag, typename... Cs>
  constexpr auto evaluate(Environment const& env, Tag const& tag, Cs const&... cs)
  {
    evaluator<Environment> ev{env};
    return evaluate(tag, ev.visit(cs)...);
  }
}
