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

  TTS_CONSTEXPR_EXPECT    ( nucog::match($(var)       , $(var)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::var_  , $(var)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::expr_ , $(var)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::term_ , $(var)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(0_c          , $(var)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(other_var) , $(var)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::lit_  , $(var)) );

  TTS_CONSTEXPR_EXPECT    ( nucog::match(0_c         , nucog::as_expr(0_c)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::expr_, nucog::as_expr(0_c)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::term_, nucog::as_expr(0_c)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::lit_ , nucog::as_expr(0_c)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::var_ , nucog::as_expr(0_c)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(4.          , nucog::as_expr(4_c)) );

  TTS_CONSTEXPR_EXPECT    ( nucog::match( 77          , nucog::as_expr(4)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::expr_ , nucog::as_expr(4)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::term_ , nucog::as_expr(4)) );
  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::lit_  , nucog::as_expr(4)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match( 4.          , nucog::as_expr(4)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::var_  , nucog::as_expr(0)) );
};

TTS_CASE( "Check match for unary node" )
{
  using namespace nucog::literal;

  TTS_CONSTEXPR_EXPECT( nucog::match(+$(var)              ,+$(var)) );
  TTS_CONSTEXPR_EXPECT( nucog::match(+nucog::term_        ,+$(var)) );
  TTS_CONSTEXPR_EXPECT( nucog::match( nucog::expr_        ,+$(var)) );
  TTS_CONSTEXPR_EXPECT( nucog::match(+nucog::expr_        ,+$(var)) );
  TTS_CONSTEXPR_EXPECT( nucog::match( nucog::unary_expr_  ,+$(var)) );
  TTS_CONSTEXPR_EXPECT( nucog::match( nucog::nary_expr_<1>,+$(var)) );

  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var)              , +$(some_value)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(var)              , +$(some_value)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var) + $(var)      , +$(var)       ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::binary_expr_  , +$(var)       ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::ternary_expr_ , +$(var)       ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::nary_expr_<2> , +$(var)       ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(nucog::nary_expr_<7> , +$(var)       ) );
};

TTS_CASE( "Check match for binary plus" )
{
  using namespace nucog::literal;

  TTS_CONSTEXPR_EXPECT    ( nucog::match(nucog::term_ + nucog::term_, $(var) + $(cons)) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match(+$(cons)                   , $(var) + $(var) ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var) + $(cons)           , $(var) + $(var) ) );
  TTS_CONSTEXPR_EXPECT_NOT( nucog::match($(var) + $(var)            , $(var) + $(cons)) );
};
