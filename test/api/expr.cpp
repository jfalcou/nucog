//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>

TTS_CASE( "Check unary expression properties" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = -x_;

  TTS_EQUAL( f.arity()     , 1ULL );
  TTS_EQUAL( f.tag()       , nucog::tags::unary_minus_{} );
  TTS_EQUAL( f[0_c].value(), "x_"_sym );
};

TTS_CASE( "Check binary expression properties" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = x_ * x_;

  TTS_EQUAL( f.arity()           , 2ULL                       );
  TTS_EQUAL( f.tag()             , nucog::tags::multiplies_{} );
  TTS_EQUAL( f[0_c].value(), "x_"_sym                         );
  TTS_EQUAL( f[1_c].value(), "x_"_sym                         );
};
