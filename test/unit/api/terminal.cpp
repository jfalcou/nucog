//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <nucog/expr/terminal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE( "Check terminal properties" )
{
  using namespace nucog::literal;

  auto s1  = $(x_);

  TTS_EQUAL( s1.arity()     , 0                        );
  TTS_EQUAL( s1.tag()       , nucog::tags::terminal_{} );
  TTS_EQUAL( s1.value().id(), "x_"_sym.id()            );
}
