//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>

TTS_CASE( "Check evaluate visitor over terminal" )
{
  using namespace nucog::literal;

  auto f = $(var);
  TTS_EQUAL  ( f($(var) = 42.69), 42.69);
  TTS_EXPR_IS( f($(var) = 42.69), double);
};

TTS_CASE( "Check evaluate visitor over unary expression" )
{
  using nucog::x_;
  using nucog::y_;

  auto f = -x_;
  auto g = +y_;

  TTS_EQUAL( f(x_ = 42.69), -42.69);
  TTS_EQUAL( g(y_ = 1337 ), 1337  );
};

TTS_CASE( "Check evaluate visitor over binary expression" )
{
  using nucog::x_;
  using nucog::y_;
  using nucog::z_;

  TTS_EQUAL( (x_ + x_)( x_ = 4.5f )         ,  9.f);
  TTS_EQUAL( (y_ + x_)( x_ = 40 , y_ = 2.f ), 42.f);
  TTS_EQUAL( (x_ + y_)( y_ = 40., x_ = 0x02), 42. );
  TTS_EQUAL( (x_ - y_)( y_ = 8  , x_ = 50. ), 42. );
  TTS_EQUAL( (y_ - x_)( y_ = 50 , x_ = 8.f ), 42.f);
};
