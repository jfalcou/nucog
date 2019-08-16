//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_SYMBOL_HPP_INCLUDED
#define NUCOG_SYMBOL_HPP_INCLUDED

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

#endif