//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <nucog/components/literal.hpp>
#include <nucog/components/terminal.hpp>

namespace nucog
{
  namespace naming
  {
    using namespace nucog::literals;

    inline constexpr auto x_  = $(x_);
    inline constexpr auto y_  = $(y_);
    inline constexpr auto z_  = $(z_);
  }

  using naming::x_;
  using naming::y_;
  using naming::z_;
}
