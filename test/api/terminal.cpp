//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/components/terminal.hpp>

TTS_CASE( "Check terminal properties" )
{
  using namespace nucog::literals;

  auto s1  = $(x_);

  TTS_EQUAL( s1.arity(), 0                        );
  TTS_EQUAL( s1.tag()  , nucog::tags::terminal_{} );
  TTS_EQUAL( s1.value(), "x_"_sym                 );
};
