#!/bin/bash

rm build
mkdir build
cd build
cmake ..
make
cd ..
mv build/binary bin/binary
#bin/binary_$(date +%m-%d-%Y-%H:%M)