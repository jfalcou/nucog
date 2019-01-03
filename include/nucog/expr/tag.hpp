//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright 2019 Joel FALCOU
  Copyright 2019 Vincent REVERDY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NUCOG_EXPR_TAG_HPP_INCLUDED
#define NUCOG_EXPR_TAG_HPP_INCLUDED

#include <type_traits>

namespace nucog
{
  template<typename Tag> struct tag
  {
    using tag_type = Tag;

    template<typename Other> constexpr bool operator==(Other const& o) const noexcept
    {
      return std::is_same_v<Other,Tag>;
    }

    template<typename Other> constexpr bool operator!=(Other const& o) const noexcept
    {
      return !std::is_same_v<Other,Tag>;
    }
  };
}

#endif
