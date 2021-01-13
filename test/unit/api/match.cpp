//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/expr/match.hpp>
#include <nucog/expr/terminal.hpp>
#include <nucog/ops/minus.hpp>
#include <nucog/ops/plus.hpp>
#include <nucog/ops/unary_minus.hpp>
#include <nucog/ops/unary_plus.hpp>
#include <nucog/symbol.hpp>

TTS_CASE( "Check match for terminal" )
{
  using namespace nucog;
  using namespace nucog::literal;

  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(x_, x_    ) >::value    );
  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(x_, var_  ) >::value  );
  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(x_, expr_ ) >::value );
  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(x_, term_ ) >::value );

  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(as_expr(0_c), 0_c ) >::value );
  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(as_expr(4)  ,  77 ) >::value );

  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(as_expr(4),  4. ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(x_        , 0_c ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(x_        ,  y_ ) >::value );
}

TTS_CASE( "Check match for unary plus" )
{
  using namespace nucog;

  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(+x_,+x_)    >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(+x_,+term_) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(+x_, expr_ ) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(+x_,+expr_) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(+x_, unary_expr_   ) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(+x_, nary_expr_<1> ) >::value );

  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(+y_,+x_)            >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(+x_,x_ + x_)        >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(+x_,binary_expr_  ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(+x_,ternary_expr_ ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(+x_,nary_expr_<2> ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(+x_,nary_expr_<7> ) >::value );
}

TTS_CASE( "Check match for unary minus" )
{
  using namespace nucog;

  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(-x_,-x_)    >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(-x_,-term_) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(-x_,-expr_ ) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(-x_, expr_ ) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(-x_, unary_expr_   ) >::value );
  TTS_EXPECT( std::bool_constant<  NUCOG_MATCH(-x_, nary_expr_<1> ) >::value );

  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(-y_,-x_)            >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(-x_,x_ + x_)        >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(-x_,binary_expr_  ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(-x_,ternary_expr_ ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(-x_,nary_expr_<2> ) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(-x_,nary_expr_<7> ) >::value );
}

TTS_CASE( "Check match for binary plus" )
{
  using namespace nucog;
  using namespace nucog::literal;

  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(x_ + y_, term_ + term_) >::value );
  TTS_EXPECT( std::bool_constant< NUCOG_MATCH(x_ + x_, 2_c * x_) >::value );

  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(x_ + x_, + y_)    >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(x_ + x_, x_ + y_) >::value );
  TTS_EXPECT_NOT( std::bool_constant< NUCOG_MATCH(x_ + y_, x_ + x_) >::value );
}
