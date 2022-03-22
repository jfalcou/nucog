//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <nucog/deps/kumi.hpp>

namespace nucog
{
  struct evaluator
  {
    using nucog_evaluator = void;

    template<typename Environment, typename Expression>
    constexpr auto accept(Environment const& env, Expression const& expr) const
    {
      return visit(env, expr);
    }

    template<typename Environment, typename Expression>
    constexpr auto visit(Environment const& env, Expression const& expr) const
    {
      constexpr auto tag = Expression::tag();
      if constexpr(Expression::arity() == 0)
      {
        return evaluate(env, tag, expr.value());
      }
      else
      {
        return  kumi::apply ( [&](auto const&... cs) { return evaluate(tag, visit(env, cs)...); }
                            , expr.children()
                            );
      }
    }
  };
}
