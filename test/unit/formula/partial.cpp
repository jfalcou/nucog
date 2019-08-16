//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <nucog/visitor/display.hpp>
#include <nucog/visitor/evaluate.hpp>
#include <nucog/ops/plus.hpp>
#include <nucog/ops/times.hpp>
#include <nucog/symbol.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

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
