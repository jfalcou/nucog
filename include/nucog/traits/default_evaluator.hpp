//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/traits/evaluate.hpp>

namespace nucog
{
  template<typename... T> struct default_evaluator
  {
    using type = evaluator;
  };

  template<typename T>
  concept expr_evaluator = requires(T const&)
  {
    typename T::nucog_evaluator;
  };
}
