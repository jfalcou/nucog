//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>

namespace nucog
{
  template<typename Tag> struct tag;

  template<> struct tag<void>
  {
    using tag_type = void;

    template<typename Other> constexpr bool operator==(Other const&) const noexcept
    {
      return true;
    }

    template<typename Other> constexpr bool operator!=(Other const&) const noexcept
    {
      return false;
    }
  };

  using any_tag = tag<void>;

  template<typename Tag> struct tag
  {
    using tag_type = Tag;

    template<typename Other> constexpr bool operator==(Other const& o) const noexcept
    {
      return std::is_same_v<Other,Tag> || std::is_same_v<Other,any_tag>;
    }

    template<typename Other> constexpr bool operator!=(Other const& o) const noexcept
    {
      return !(*this == o);
    }
  };

  using any_tag = tag<void>;
}
