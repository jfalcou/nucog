//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <nucog/nucog.hpp>
#include <type_traits>
#include <vector>
#include <cassert>

//==================================================================================================
// Defines a custom evaluator and ties it to a specific signature
//==================================================================================================

//==================================================================================================
// Am I a std::vector ?
template<typename T> struct is_vector : std::false_type {};

template<typename T, typename A>
struct is_vector<std::vector<T,A>> : std::true_type {};

//==================================================================================================
// Grab ::value_type from T ot return T of T has no such type
template<typename T> struct value_type  { using type = T;};

template<typename T>
requires requires(T const&) { typename T::value_type; }
struct value_type<T> { using type = typename T::value_type; };

//==================================================================================================
// Evaluates a nucog::expression while taking care of potential vector<>
struct vector_evaluator
{
  using nucog_evaluator = void;

  //================================================================================================
  // T::size() or 1 depending on the fact T is a vector
  template<typename T>
  static constexpr std::size_t size(T const& c)
  {
    if constexpr( is_vector<T>::value ) return c.size(); else return 1;
  }

  //================================================================================================
  // T[i] or T depending on the fact T is a vector
  template<typename T>
  static constexpr auto value(T const& c, std::size_t i)
  {
    if constexpr( is_vector<T>::value ) return c[i]; else return c;
  }

  //================================================================================================
  // Is a size equal to 1 (scalar) or the precomputec vector size (n) ?
  template<typename T>
  static constexpr bool is_valid(T const& c, std::size_t n)
  {
    return size(c) == 1 || size(c) == n;
  }

  //================================================================================================
  // Accept to visit the expression
  template<typename... Opts, typename Expression>
  constexpr auto accept(rbr::settings<Opts...> const& env, Expression const& expr) const
  {
    //  - Computes the type and size required by the output
    std::size_t sz = 1;
    ((sz = std::max(sz, size(env[typename Opts::keyword_type{}]))),...);
    using out_t = std::common_type_t<typename value_type<typename Opts::stored_value_type>::type...>;

    //  - Checks all vectors have same size or assert
    assert(   (is_valid(env[typename Opts::keyword_type{}], sz) && ...)
          &&  "Size mismatch in vector parameters"
          );

    std::vector<out_t> out(sz);

    // Iterates over all index and "visit"
    for(std::size_t i = 0;i < sz;++i)
      out[i] = visit(env, expr, i);

    return out;
  }

  template<typename Environment, typename Expression>
  constexpr auto visit(Environment const& env, Expression const& expr, std::size_t i) const
  {
    constexpr auto tag = Expression::tag();
    if constexpr(Expression::arity() == 0)
    {
      // Extract value from the terminals
      return value(nucog::evaluate(env, tag, expr.value()), i);
    }
    else
    {
      // Recursively visit children and use default evaluator
      return  kumi::apply ( [&](auto const&... cs)
                            {
                              return nucog::evaluate(tag, visit(env, cs, i)...);
                            }
                          , expr.children()
                          );
    }
  }
};

//==================================================================================================
// Register vector_evaluator as a default evaluator if *at least* one terminal is a vector
template<typename... T>
requires( (is_vector<T>::value || ...) )
struct nucog::default_evaluator<T...>
{
  using type = vector_evaluator;
};


TTS_CASE( "Check array_evaluate visitor over terminal" )
{
  using namespace nucog::literal;

  auto f = $(v1) + $(v2);

  // Checks forced evaluator
  auto f00 = f( vector_evaluator{}, $(v1) = 35, $(v2) = 8.5  );
  TTS_EQUAL(f00, std::vector<double>{43.5});

  std::vector<float> b{1.f,2.f,3.f,4.f,5.f};
  std::vector<int>   c{  9,  8,  7,  6,  5};

  std::vector<float> rvv{10.f,10.f,10.f,10.f,10.f};
  std::vector<float> rvs{7.f,8.f,9.f,10.f,11.f};

  auto fvv = f( $(v1) = b, $(v2) = c  );
  TTS_EQUAL(fvv, rvv);
  TTS_EQUAL(fvv.size(), 5ULL);

  auto fvs = f( $(v1) = b, $(v2) = 6  );
  TTS_EQUAL(fvs, rvs);
  TTS_EQUAL(fvs.size(), 5ULL);

  auto fsv = f( $(v1) = 6, $(v2) = b  );
  TTS_EQUAL(fsv, rvs);
  TTS_EQUAL(fsv.size(), 5ULL);
};
