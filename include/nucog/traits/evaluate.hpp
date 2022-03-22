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
      constexpr auto tag = Expression::tag();
      if constexpr(Expression::arity() == 0)
      {
        return evaluate(env_,tag, expr.value());
      }
      else
      {
        return  kumi::apply ( [&](auto const&... cs) { return visit(tag, visit(cs)...); }
                            , expr.children()
                            );
      }
    }

    template<typename Tag, typename... Cs>
    constexpr auto visit(Tag const& tag, Cs const&... cs)
    {
      return evaluate(env_, tag, visit(cs)...);
    }

    constexpr Environment const& env() { return env_; }

    Environment const& env_;
  };
}
