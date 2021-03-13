//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/expr/terminal.hpp>

namespace nucog
{
  namespace naming
  {
    using namespace nucog::literal;

    inline constexpr auto x_  = $(x_);
    inline constexpr auto y_  = $(y_);
    inline constexpr auto z_  = $(z_);
  }

  using naming::x_;
  using naming::y_;
  using naming::z_;
}
