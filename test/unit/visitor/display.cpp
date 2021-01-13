//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/visitor/display.hpp>
#include <nucog/ops/minus.hpp>
#include <nucog/ops/plus.hpp>
#include <nucog/ops/unary_minus.hpp>
#include <nucog/ops/unary_plus.hpp>
#include <nucog/symbol.hpp>
#include <sstream>

TTS_CASE( "Check display visitor over terminal" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;

  std::ostringstream s;
  auto d = display(s, x_).str();
  TTS_EQUAL(d, "x_");

  std::ostringstream r;
  auto e = display(r, $(random_variable)).str();
  TTS_EQUAL(e, "random_variable");
}

TTS_CASE( "Check display visitor over unary expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;

  std::ostringstream r0;
  auto s0 = display(r0, +x_).str();
  TTS_EQUAL(s0, "+(x_)");

  std::ostringstream r1;
  auto s1 = display(r1, +(+x_)).str();
  TTS_EQUAL(s1, "+(+(x_))");

  std::ostringstream r2;
  auto s2 = display(r2, +(-(+x_)) ).str();
  TTS_EQUAL(s2, "+(-(+(x_)))");
}

TTS_CASE( "Check display visitor over binary expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;
  using nucog::z_;

  std::ostringstream r0;
  auto s0 = display(r0, y_ + 3.f).str();
  TTS_EQUAL(s0, "(y_ + 3)");

  std::ostringstream r1;
  auto s1 = display(r1, y_ + x_).str();
  TTS_EQUAL(s1, "(y_ + x_)");

  std::ostringstream r2;
  auto s2 = display(r2, y_ - x_ ).str();
  TTS_EQUAL(s2, "(y_ - x_)");

  std::ostringstream r3;
  auto s3 = display(r3, x_ + y_ - z_ ).str();
  TTS_EQUAL(s3, "((x_ + y_) - z_)");

  std::ostringstream r4;
  auto s4 = display(r4, x_ + x_ ).str();
  TTS_EQUAL(s4, "(2 * x_)");
}
