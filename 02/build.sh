#!/bin/sh

set -xe

# echo "Running solution written in C"
gcc-13 -o main main.c -pedantic -Wall -Wextra -g
./main

# echo "\nRunning solution written in Rust"
# rustc main.rs
# ./main
