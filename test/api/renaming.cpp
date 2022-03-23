//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>

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
  r << g;
  auto e = r.str();
  TTS_EQUAL(e, "(1 + (y_ * y_))"s);

  auto h = z_ + x_*y_;
  auto hh = h(z_ = x_)( x_ = y_ );

  std::ostringstream s;
  s << hh;
  auto ee = s.str();
  TTS_EQUAL(ee, "(y_ + (y_ * y_))"s);
};
