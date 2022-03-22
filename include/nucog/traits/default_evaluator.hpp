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
  template<typename Env, typename... T> struct default_evaluator
  {
    using type = evaluator<Env>;
  };
}
