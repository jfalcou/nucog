//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/literal.hpp>
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
