//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/visitor/display.hpp>
#include <nucog/visitor/evaluate.hpp>
#include <nucog/ops/plus.hpp>
#include <nucog/ops/times.hpp>
#include <nucog/symbol.hpp>

TTS_CASE( "Check partial evaluation of expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;
  using nucog::z_;

  auto f = 3*z_ + x_*y_;
  auto g = f(x_ = 10);

  std::ostringstream r;
  auto e = display(r, g).str();
  TTS_EQUAL(e, "((3 * z_) + (10 * y_))");
}
