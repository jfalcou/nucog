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
        return  kumi::apply ( [&](auto const&... cs) { return evaluate(tag, visit(cs)...); }
                            , expr.children()
                            );
      }
    }

    constexpr Environment const& env() { return env_; }

    Environment const& env_;
  };
}
