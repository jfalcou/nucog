//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <tts/tts.hpp>
#include <nucog/components/literal.hpp>
#include <string>

TTS_CASE( "Check uniqueness of literal types " )
{
  using namespace nucog::literals;

  TTS_TYPE_IS   (  decltype("symbol_1"_sym), decltype("symbol_1"_sym) );
  TTS_EXPECT_NOT(( std::is_same_v<decltype("symbol_1"_sym), decltype("alas, symbol_2"_sym)> ));
};
