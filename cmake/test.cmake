##==================================================================================================
##  NuCoG - Numerical Code Generator
##  Copyright : NuCog Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(add_parent_target)

##==================================================================================================
## Centralize all required setup for unit tests
##==================================================================================================
function(add_unit_test root)
  if( MSVC )
    set( options /std:c++latest -W3 -EHsc)
  else()
    set( options -std=c++20 -Wall -Wno-missing-braces )
  endif()

  foreach(file ${ARGN})
    string(REPLACE ".cpp" ".unit" base ${file})
    string(REPLACE "/"    "." base ${base})
    string(REPLACE "\\"   "." base ${base})
    set(test "${root}.${base}")

    add_executable( ${test}  ${file})
    target_compile_options  ( ${test} PUBLIC ${options} )

    set_property( TARGET ${test}
                  PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                )

    if (CMAKE_CROSSCOMPILING_CMD)
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}> --no-color --pass
              )
    else()
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND $<TARGET_FILE:${test}> --no-color --pass
              )
    endif()

    set_target_properties ( ${test} PROPERTIES
                            EXCLUDE_FROM_DEFAULT_BUILD TRUE
                            EXCLUDE_FROM_ALL TRUE
                            ${MAKE_UNIT_TARGET_PROPERTIES}
                          )

    target_include_directories( ${test}
                                PRIVATE
                                  ${tts_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/test
                                  ${PROJECT_SOURCE_DIR}/include
                              )

    add_dependencies(unit ${test})

    add_parent_target(${test})
  endforeach()
endfunction()

##==================================================================================================
## Setup TTS
##==================================================================================================
set(TTS_BUILD_TEST    OFF CACHE INTERNAL "OFF")
set(TTS_IS_DEPENDENT  ON  CACHE INTERNAL "ON")

include(FetchContent)
FetchContent_Declare( tts
                      GIT_REPOSITORY https://github.com/jfalcou/tts.git
                      GIT_TAG develop
                    )

FetchContent_MakeAvailable(tts)

## Setup our tests
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
