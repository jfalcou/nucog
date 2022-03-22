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

template<typename T> struct is_vector : std::false_type {};

template<typename T, typename A>
struct is_vector<std::vector<T,A>> : std::true_type {};

template<typename T> struct value_type  { using type = T;};

template<typename T>
requires requires(T const&) { typename T::value_type; }
struct value_type<T> { using type = typename T::value_type; };

struct vector_evaluator
{
  using nucog_evaluator = void;

  template<typename T>
  static constexpr std::size_t size(T const& c)
  {
    if constexpr( requires(T const& t) { t.size(); }) return c.size(); else return 1;
  }

  template<typename T>
  static constexpr auto value(T const& c, std::size_t i)
  {
    if constexpr( requires(T const& t) { t[i]; }) return c[i]; else return c;
  }

  template<typename T>
  static constexpr bool is_valid(T const& c, std::size_t n)
  {
    return size(c) == 1 || size(c) == n;
  }

  template<typename... Opts, typename Expression>
  constexpr auto accept(rbr::settings<Opts...> const& env, Expression const& expr) const
  {
    std::size_t sz = 1;
    ((sz = std::max(sz, size(env[typename Opts::keyword_type{}]))),...);
    using out_t = std::common_type_t<typename value_type<typename Opts::stored_value_type>::type...>;

    assert(   (is_valid(env[typename Opts::keyword_type{}], sz) && ...)
          &&  "Size mismatch in vector parameters"
          );

    std::vector<out_t> out(sz);

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
      return value(nucog::evaluate(env, tag, expr.value()), i);
    }
    else
    {
      return  kumi::apply ( [&](auto const&... cs)
                            {
                              return nucog::evaluate(tag, visit(env, cs, i)...);
                            }
                          , expr.children()
                          );
    }
  }
};

template<typename... T>
requires( (is_vector<T>::value || ...) )
struct nucog::default_evaluator<T...>
{
  using type = vector_evaluator;
};


TTS_CASE( "Check array_evaluate visitor over terminal" )
{
  using namespace nucog::literal;

  auto f = $(yolo) + $(uwu);

  auto f00 = f( vector_evaluator{}, $(yolo) = 3.5f, $(uwu) = 8.6  );
  std::cout << f00.front() << "\n";

  std::vector<float> b{1.2f,2.3f,3.4f,4.5f,5.6f};
  std::vector<int>   c{   9,   8,   7,   6,   5};

  auto fvv = f( $(yolo) = b, $(uwu) = c  );
  for(auto e : fvv) std::cout << e << " ";
  std::cout << "\n";

  auto fvs = f( $(yolo) = b, $(uwu) = 6  );
  for(auto e : fvs) std::cout << e << " ";
  std::cout << "\n";

  auto fsv = f( $(yolo) = 9, $(uwu) = b  );
  for(auto e : fsv) std::cout << e << " ";
  std::cout << "\n";
};
