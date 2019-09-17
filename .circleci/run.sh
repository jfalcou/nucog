##==================================================================================================
##  NuCoG - Numerical Code Generator
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Vincent Reverdy
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

mkdir -p build
cd build

cmake .. -G Ninja -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS"

echo "ninja unit -j $REPLICATION"
ninja unit -j $REPLICATION

echo "ctest unit -j 8"
ctest -R unit -j 8
