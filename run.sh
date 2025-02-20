#!/bin/bash

# Enable error handling
set -e

# Check if the executable exists
if [ ! -f "out/bakery" ]; then
    echo "Did not find executable!"
    exit 1
fi

# Run the executable
./out/bakery
