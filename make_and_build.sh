#!/bin/bash

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/Users/arod183/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
