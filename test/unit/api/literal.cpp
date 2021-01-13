//==================================================================================================
/*
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <nucog/literal.hpp>
#include <nucog/detail/type_map.hpp>
#include <string>

TTS_CASE( "Check uniqueness of literal types " )
{
  using namespace nucog::literal;

  TTS_TYPE_IS   (  decltype("symbol_1"_sym), decltype("symbol_1"_sym) );
  TTS_EXPECT_NOT(( std::is_same_v<decltype("symbol_1"_sym), decltype("alas, symbol_2"_sym)> ));
}

TTS_CASE( "Check uniqueness of literal values " )
{
  using namespace nucog::literal;

  auto s1  = "variable 1"_sym;
  auto s1p = "variable 1"_sym;
  auto s2  = "alas, another variable"_sym;

  TTS_EQUAL    ( s1, s1p );
  TTS_NOT_EQUAL( s1, s2  );
}

TTS_CASE( "Check symbol interface for named parameters" )
{
  using namespace nucog::literal;
  using namespace std::string_literals;

  auto xx_ = "xx"_sym;
  auto yy_ = "yy"_sym;
  auto zz_ = "zz"_sym;

  short       i = 1337;
  char const  z = 'Z';

  auto t = nucog::type_map(yy_ = "tests"s, xx_ = i, zz_ = z);

  TTS_EQUAL(  t(xx_),  i);
  TTS_EQUAL(  t(yy_), "tests"s);
  TTS_EQUAL(  t(zz_), 'Z');
}
