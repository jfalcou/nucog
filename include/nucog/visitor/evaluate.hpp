//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_VISITOR_EVALUATE_HPP_INCLUDED
#define NUCOG_VISITOR_EVALUATE_HPP_INCLUDED

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
        return  detail::apply<Expression::arity()>
                ( [&](auto const&... idx) -> decltype(auto)
                  {
                    return evaluate( env_, Expression::tag(), expr[idx]... );
                  }
                );
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

#endif
