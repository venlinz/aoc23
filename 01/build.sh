#!/bin/sh

set -xe

echo "Running solution written in C"
gcc-13 -o mainc main.c -pedantic -Wall -Wextra -L$LOCAL_LIBRARY_LIB_PATH -I$LOCAL_LIBRARY_INCLUDE_PATH -lstrings
./mainc

echo "\nRunning solution written in Rust"
rustc main.rs
./main
