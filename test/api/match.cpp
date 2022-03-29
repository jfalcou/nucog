//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>

TTS_CASE( "Check match for terminal" )
{
  using namespace nucog::literal;

  TTS_CONSTEXPR_EXPECT( nucog::match($(var), $(var)       ) );
  TTS_CONSTEXPR_EXPECT( nucog::match($(var), nucog::var_  ) );
  TTS_CONSTEXPR_EXPECT( nucog::match($(var), nucog::expr_ ) );
  TTS_CONSTEXPR_EXPECT( nucog::match($(var), nucog::term_ ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var)           , 0_c )         );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var)           , $(other_var) ));
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var)           , nucog::lit_  ));

  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(0_c), 0_c         ) );
  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(0_c), nucog::expr_) );
  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(0_c), nucog::term_) );
  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(0_c), nucog::lit_ ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::as_expr(0_c), nucog::var_ ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::as_expr(4_c),  4. ) );

  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(4),  77         ) );
  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(4), nucog::expr_) );
  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(4), nucog::term_) );
  TTS_CONSTEXPR_EXPECT( nucog::match(nucog::as_expr(4), nucog::lit_ ) );

  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::as_expr(4),  4.         ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::as_expr(0), nucog::var_ ) );
};

TTS_CASE( "Check match for unary node" )
{
  using namespace nucog::literal;

  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var),+$(var)        )       );
  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var),+nucog::term_  )       );
  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var), nucog::expr_  )       );
  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var),+nucog::expr_  )       );
  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var), nucog::unary_expr_   ));
  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var), nucog::nary_expr_<1> ));

  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(some_value),+$(var))        );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(some_value),+$(var))        );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var),$(var) + $(var))       );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var),nucog::binary_expr_  ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var),nucog::ternary_expr_ ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var),nucog::nary_expr_<2> ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var),nucog::nary_expr_<7> ) );
};

TTS_CASE( "Check match for binary plus" )
{
  using namespace nucog::literal;

  TTS_CONSTEXPR_EXPECT    ( nucog::match($(var) + $(cons) , nucog::term_ + nucog::term_) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var) + $(var)  , +$(cons))         );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var) + $(var)  , $(var) + $(cons)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var) + $(cons) , $(var) + $(var))  );
};
