//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_OPS_ABS_HPP_INCLUDED
#define NUCOG_OPS_ABS_HPP_INCLUDED

#include <nucog/expr/as_expr.hpp>
#include <nucog/expr/expr.hpp>
#include <nucog/ops/function.hpp>
#include <nucog/ops/make.hpp>
#include <iostream>

namespace nucog::detail
{
  struct abs_
  {
    template<typename T> constexpr auto operator()(T&& x) const
    {
      return std::abs(std::forward<T>(x));
    }
  };

  inline std::ostream& operator<<(std::ostream& os, abs_ const&)
  {
    return os << "abs";
  }
}

namespace nucog
{
  // -----------------------------------------------------------------------------------------------
  // Function injection
  template<typename XHS> constexpr auto abs( XHS&& xhs ) noexcept
  {
    return fun(detail::abs_{}, std::forward<XHS>(xhs));
  }
}

#endif
