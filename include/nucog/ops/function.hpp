//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/detail/supports_overload.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/expr/node.hpp>
#include <nucog/expr/tag.hpp>
#include <nucog/visitor/display.hpp>
#include <nucog/visitor/evaluate.hpp>
#include <iostream>

namespace nucog::tags
{
  struct function_ : tag<function_> {};
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Function builder
  template<typename Fn, typename... XHS>
  constexpr auto build(tags::function_ const&, expr<Fn> const& fn, expr<XHS> const&... xhs) noexcept
  {
    return node<tags::function_,Fn,XHS...>{fn.self(), xhs.self()...};
  }

  // -----------------------------------------------------------------------------------------------
  // Builder helper
  template<typename Tag, typename XHS> constexpr auto fun( Tag const& t, XHS&& xhs ) noexcept
  {
    return make(tags::function_{},as_expr(t), as_expr(std::forward<XHS>(xhs)));
  }

  // -----------------------------------------------------------------------------------------------
  // Display support
  template<typename Stream, typename Fn, typename Cs>
  Stream& display(Stream& os, tags::function_ const&, Fn const& f, Cs const& cs)
  {
    display_visitor<Stream> v{os};

    v.visit(f);
    os << '(';

    v.visit(cs);
    os << ')';

    return os;
  }

  template<typename Stream, typename Fn, typename... Cs>
  Stream& display(Stream& os, tags::function_ const&, Fn const& f, Cs const&... cs)
  {
    display_visitor<Stream> v{os};

    v.visit(f);
    os << '(';

    auto p = [&](auto const& c) { os << ", "; v.visit(c); };
    (p(cs), ...);

    os << ')';

    return os;
  }

  // -----------------------------------------------------------------------------------------------
  // Evaluation support
  template<typename Environment, typename Fn, typename Cs>
  constexpr auto evaluate(Environment const& env, tags::function_, Fn const& f, Cs const& cs)
  {
    puts("Evaluate like a function_");
    evaluate_visitor<Environment> ev{env};
std::cout << "cs -> " << ev.visit(cs) << "\n";
    return (f.value())( ev.visit(cs) );
  }

}
