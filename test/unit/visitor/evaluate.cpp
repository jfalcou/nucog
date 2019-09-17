//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <nucog/ops/minus.hpp>
#include <nucog/ops/plus.hpp>
#include <nucog/ops/unary_minus.hpp>
#include <nucog/ops/unary_plus.hpp>
#include <nucog/visitor/evaluate.hpp>
#include <nucog/symbol.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check evaluate visitor over terminal" )
{
  using namespace nucog::literal;

  auto f = $(var);
  TTS_EQUAL  ( f($(var) = 42.69), 42.69);
  TTS_EXPR_IS( f($(var) = 42.69), double);
}

TTS_CASE( "Check evaluate visitor over unary expression" )
{
  using nucog::x_;
  using nucog::y_;

  auto f = -x_;
  auto g = +y_;

  TTS_EQUAL( f(x_ = 42.69), -42.69);
  TTS_EQUAL( g(y_ = 1337) , 1337  );
}

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
}

//  std::cout << ( (y_ - z_) - (x_ + y_) )( y_ = 3, x_ = 8, z_ = 1.2345) << "\n";
  // auto f = x_ + y_ + z_;
  // auto g = f(x_ = y_, z_ = y_);
  // std::cout << g(y_ = 10) << "\n";

  // auto f1 = y_ + 3;
  // auto f2 = x_ + 1;
  // auto f12 = f1(y_ = f2);
  // std::cout << f12(x_ = 6) << "\n";
