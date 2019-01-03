##==================================================================================================
##  NuCoG - Numerical Code Generator
##  Copyright 2019 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)
## =================================================================================================
## Setup project
## =================================================================================================
project(nucog LANGUAGES CXX)
set(PROJECT_VERSION 1.18.6.0)
set(PROJECT_DOC_DIR   ${PROJECT_SOURCE_DIR}/doc)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

## =================================================================================================
## No in-source build
## =================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message( FATAL_ERROR "[nucog] Building in-source, not recommended! Build in a separate directory." )
endif()

## =================================================================================================
## Add include directories
## =================================================================================================
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/test
  ${PROJECT_SOURCE_DIR}/benchmark
)

## =================================================================================================
## Compute version string and mode
## =================================================================================================
include(parse_revision)

## =================================================================================================
## Options
## =================================================================================================
option( NUCOG_BUILD_TEST        "Build tests for nucog"         ON  )
option( NUCOG_BUILD_BENCHMARKS  "Build benchmarks for nucog"    OFF )
option( NUCOG_BUILD_DOC         "Build documentation for nucog" ON  )

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION .)

## =================================================================================================
## Setup Documentation
## =================================================================================================
if( NUCOG_BUILD_DOC )
  add_subdirectory(doc)
endif()

## =================================================================================================
## Test and Benchmarks target
## =================================================================================================
include(CTest)

if( NUCOG_BUILD_TEST )
  include(test)
endif()

if( NUCOG_BUILD_BENCHMARKS )
  include(benchmark)
endif()
