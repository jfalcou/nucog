##==================================================================================================
##  NuCoG - Numerical Code Generator
##  Copyright 2019 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

function(add_parent_target target)
  string(REGEX REPLACE "[^.]+\\.([^.]+)$" "\\1" parent_target ${target})
  string(REGEX REPLACE "^.*\\.([^.]+)$" "\\1" suffix ${parent_target})

  if(NOT TARGET ${target})
    add_custom_target(${target})
    set_property(TARGET ${target} PROPERTY FOLDER ${suffix})
  endif()

  if(NOT ${parent_target} STREQUAL ${target})
    add_parent_target(${parent_target})
    add_dependencies(${parent_target} ${target})
  endif()
endfunction()
