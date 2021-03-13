//==================================================================================================
/**
  NuCoG - Numerical Code Generator
  Copyright : NuCoG Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <utility>
#include <cstddef>

namespace nucog::detail
{
  template<std::size_t N> struct fixed_string
  {
    char content[N];
    using char_type = char;

    constexpr fixed_string(const char (&input)[N]) noexcept
            : fixed_string(input, std::make_index_sequence<N>())
    {}

    template <size_t... I>
    constexpr fixed_string(const char (&input)[N], std::index_sequence<I...>) noexcept
            : content{input[I]...}
    {}

    constexpr size_t size() const noexcept { if (content[N-1] == '\0') return N-1; else return N; }

    constexpr char        operator[](size_t i)  const noexcept { return content[i];       }
    constexpr const char* begin()               const noexcept { return content;          }
    constexpr const char* end()                 const noexcept { return content + size(); }
  };

  template<> class fixed_string<0>
  {
    public:
    using char_type = char;
    constexpr fixed_string(const char *) noexcept {}
    constexpr std::size_t size()  const noexcept { return 0; }
    constexpr const char* begin() const noexcept { return nullptr; }
    constexpr const char* end()   const noexcept { return nullptr; }
  };

  template <std::size_t N> fixed_string(const char (&)[N]) -> fixed_string<N>;
}
