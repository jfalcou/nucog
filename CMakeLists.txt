##==================================================================================================
##  NUCOG - Cmpact C++20 Tuple Toolbox
##  Copyright : NUCOG Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)

##==================================================================================================
## Setup project
##==================================================================================================
project(nucog LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[nucog]: In-source build is not recommend")
endif()

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/nucog TYPE INCLUDE)

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(nucog_lib INTERFACE)
target_include_directories(nucog_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_features(nucog_lib INTERFACE cxx_std_20)
add_library(nucog::nucog ALIAS nucog_lib)

##==================================================================================================
## Options
##==================================================================================================
option( NUCOG_BUILD_TEST  "Build tests for nucog" ON )

##==================================================================================================
## Test target
##==================================================================================================
if( NUCOG_BUILD_TEST )
  include(CTest)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
endif()
