##==================================================================================================
##  NuCoG - Numerical Code Generator
##  Copyright : NuCog Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

apt-get update && apt-get install -y sudo && rm -rf /var/lib/apt/lists/*
apt-get update && sudo apt-get install -y cmake
apt-get update && sudo apt-get install -y ninja-build

if hash "git" 2>/dev/null; then
  git --version;
else
  apt-get update && sudo apt-get install -y git;
fi
