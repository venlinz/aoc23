#!/bin/sh

set -xe

gcc-13  -pedantic -Wall -Wextra -g -o main main.c -L$LOCAL_LIBRARY_LIB_PATH -I$LOCAL_LIBRARY_INCLUDE_PATH -lstrings
./main

# echo "\nRunning solution written in Rust"
# rustc main.rs
# ./main
