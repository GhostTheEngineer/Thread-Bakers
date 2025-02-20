#!/bin/bash

# Enable error handling
set -e

# Check if 'out' directory exists, create it if not
if [ ! -d "out" ]; then
    mkdir out
fi

# Compile the C++ source code
g++ -o ./out/bakery -std=c++17 ./src/main.cpp
