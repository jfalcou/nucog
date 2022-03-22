//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>

TTS_CASE( "Check partial evaluation of expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;
  using nucog::z_;

  auto f = 3*x_ + x_*y_;
  auto g = f(x_ = 10 + z_);

  std::ostringstream r;
  r << g;
  auto e = r.str();
  TTS_EQUAL(e, "((3 * (10 + z_)) + ((10 + z_) * y_))"s);
};
