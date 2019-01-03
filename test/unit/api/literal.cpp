//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <nucog/literal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check uniqueness of literal types " )
{
  using namespace nucog::literal;

  TTS_TYPE_IS   (  decltype("symbol_1"_sym), decltype("symbol_1"_sym)                  );
  TTS_EXPECT_NOT(( std::is_same_v<decltype("symbol_1"_sym), decltype("alas, symbol_2"_sym)> ));
}

TTS_CASE( "Check uniqueness of literal values " )
{
  using namespace nucog::literal;

  auto s1  = "variable 1"_sym;
  auto s1p = "variable 1"_sym;
  auto s2  = "alas, another variable"_sym;

  TTS_EQUAL    ( s1.id(), s1p.id() );
  TTS_NOT_EQUAL( s1.id(), s2.id()  );
}
