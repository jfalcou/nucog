//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <nucog/expr/terminal.hpp>
#include <nucog/ops/plus.hpp>
#include <nucog/ops/minus.hpp>
#include <nucog/symbol.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE( "Check unary expression properties" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = -x_;

  TTS_EQUAL( f.arity()           , 1                     );
  TTS_EQUAL( f.tag()             , nucog::tags::minus_{} );
  TTS_EQUAL( f.child<0>().value(), "x_"_sym              );
}

TTS_CASE( "Check binary expression properties" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = x_ * x_;

  TTS_EQUAL( f.arity()           , 2                     );
  TTS_EQUAL( f.tag()             , nucog::tags::times_{} );
  TTS_EQUAL( f.child<0>().value(), "x_"_sym              );
  TTS_EQUAL( f.child<1>().value(), "x_"_sym              );
}

TTS_CASE( "Check binary expression properties after coallescing" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = x_ + x_;

  TTS_EQUAL( f.arity()           , 2                     );
  TTS_EQUAL( f.tag()             , nucog::tags::times_{} );
  TTS_EQUAL( f.child<0>().value(), 2_c                   );
  TTS_EQUAL( f.child<1>().value(), "x_"_sym              );
}
