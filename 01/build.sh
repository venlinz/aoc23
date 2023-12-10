#!/bin/sh

set -xe

echo "Running solution written in C"
gcc-13 -o mainc main.c -pedantic -Wall -Wextra
./mainc

echo "\nRunning solution written in Rust"
rustc main.rs
./main
