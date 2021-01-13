//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019-2021 Joel FALCOU
  Copyright 2019-2021 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_VISITOR_DISPLAY_HPP_INCLUDED
#define NUCOG_VISITOR_DISPLAY_HPP_INCLUDED

#include <nucog/detail/helpers.hpp>
#include <nucog/literal.hpp>

namespace nucog
{
  enum class format { prefix, infix, postfix };

  template<typename Tag> struct display_policy
  {
    static constexpr const char*  symbol    = "<unspecified>";
    static constexpr format       notation  = format::prefix;
  };

  template<typename Stream>
  struct display_visitor
  {
    display_visitor(Stream& os) : stream_(os) {}

    template<typename Expression>
    Stream& visit(Expression const& expr)
    {
      if constexpr(Expression::arity() == 0)
      {
        return display( stream_, Expression::tag(), expr.value() );
      }
      else
      {
        return  detail::apply<Expression::arity()>
                ( [&](auto const&... idx) -> decltype(auto)
                  {
                    return display( stream_, Expression::tag(), expr[idx]... );
                  }
                );
      }
    }

    Stream& stream() { return stream_; }

    private:
    Stream& stream_;
  };

  template<typename Stream, typename Expression>
  Stream& display(Stream& os, Expression const& expr)
  {
    display_visitor<Stream> v{os};
    v.visit(expr);
    return os;
  }

  template<typename Stream, typename Tag, typename Child>
  Stream& display(Stream& os, Tag const&, Child const& c)
  {
    display_visitor<Stream> v{os};
    os << display_policy<Tag>::symbol << '(';
    v.visit(c);
    os << ')';
    return os;
  }

  template<typename Stream, typename Tag, typename C0, typename C1>
  Stream& display(Stream& os, Tag const&, C0 const& c0, C1 const& c1)
  {
    display_visitor<Stream> v{os};

    if constexpr( display_policy<Tag>::notation == format::prefix )
    {
      os << display_policy<Tag>::symbol << '(';
      v.visit(c0);
      os << ", ";
      v.visit(c1);
      os << ')';
    }
    else
    {
      os << '(';
      v.visit(c0);
      os << ' ' << display_policy<Tag>::symbol << ' ';
      v.visit(c1);
      os << ')';
    }

    return os;
  }

  template<typename Stream, typename Tag, typename C0, typename... Cs>
  Stream& display(Stream& os, Tag const&, C0 const& c0, Cs const&... cs)
  {
    display_visitor<Stream> v{os};

    os << display_policy<Tag>::symbol << '(';
    v.visit(c0);

    auto p = [&](auto const& c) { os << ", "; v.visit(c); };
    (p(cs), ...);

    os << ')';

    return os;
  }
}

#endif
