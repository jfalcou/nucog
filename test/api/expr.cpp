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

#if 0
TTS_CASE( "Check binary expression properties after coalescing 0" )
{
  using namespace nucog::literal;
  using nucog::x_;
  using nucog::y_;

  auto f = x_ + 0_c;

  TTS_EQUAL( f.arity(), 0                       );
  TTS_EQUAL( f.tag()  , nucog::tags::terminal_{});
  TTS_EQUAL( f.value(), "x_"_sym                );

  auto g = 0_c + y_;

  TTS_EQUAL( g.arity(), 0                       );
  TTS_EQUAL( g.tag()  , nucog::tags::terminal_{});
  TTS_EQUAL( g.value(), "y_"_sym                );
};

TTS_CASE( "Check binary expression properties after plus coalescing" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = x_ + x_;

  TTS_EQUAL( f.arity()     , 2                     );
  TTS_EQUAL( f.tag()       , nucog::tags::times_{} );
  TTS_EQUAL( f[0_c].value(), 2_c                   );
  TTS_EQUAL( f[1_c].value(), "x_"_sym              );
};

TTS_CASE( "Check binary expression properties after plus->times coalescing" )
{
  using namespace nucog::literal;
  using nucog::x_;

  auto f = (4_c*x_) + (7_c*x_);

  TTS_EQUAL( f.arity()     , 2                     );
  TTS_EQUAL( f.tag()       , nucog::tags::times_{} );
  TTS_EQUAL( f[0_c].value(), 11_c                  );
  TTS_EQUAL( f[1_c].value(), "x_"_sym              );
};
#endif
