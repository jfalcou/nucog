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

TTS_CASE( "Check renaming variable in expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;
  using nucog::z_;

  auto f = 1 + x_*y_;
  auto g = f( x_ = y_ );

  std::ostringstream r;
  auto e = display(r, g).str();
  TTS_EQUAL(e, "(1 + (y_ * y_))");

  auto h = z_ + x_*y_;
  auto hh = h(z_ = x_)( x_ = y_ );

  std::ostringstream s;
  auto ee = display(s, hh).str();
  TTS_EQUAL(ee, "(y_ + (y_ * y_))");
}
