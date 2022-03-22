//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>
#include <sstream>

TTS_CASE( "Check display visitor over terminal" )
{;
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;

  std::ostringstream s;
  s <<  x_;
  auto d = s.str();
  TTS_EQUAL(d, "x_"s);

  std::ostringstream r;
  r << $(random_variable);
  auto e = r.str();
  TTS_EQUAL(e, "random_variable"s);
};

TTS_CASE( "Check display visitor over unary expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;

  std::ostringstream r0;
  r0 << +x_;
  auto s0 = r0.str();
  TTS_EQUAL(s0, "+(x_)"s);

  std::ostringstream r1;
  r1 << +(+x_);
  auto s1 = r1.str();
  TTS_EQUAL(s1, "+(+(x_))"s);

  std::ostringstream r2;
  r2 << +(-(+x_));
  auto s2 = r2.str();
  TTS_EQUAL(s2, "+(-(+(x_)))"s);
};

TTS_CASE( "Check display visitor over binary expression" )
{
  using namespace std::literals;
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;
  using nucog::z_;

  std::ostringstream r0;
  r0 << y_ + 3.f;
  auto s0 = r0.str();
  TTS_EQUAL(s0, "(y_ + 3)"s);

  std::ostringstream r1;
  r1 << y_ + x_;
  auto s1 = r1.str();
  TTS_EQUAL(s1, "(y_ + x_)");

  std::ostringstream r2;
  r2 << y_ - x_;
  auto s2 = r2.str();
  TTS_EQUAL(s2, "(y_ - x_)");

  std::ostringstream r3;
  r3 << x_ + y_ * z_;
  auto s3 = r3.str();
  TTS_EQUAL(s3, "(x_ + (y_ * z_))");
};
