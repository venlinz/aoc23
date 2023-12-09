#!/bin/sh

set -xe

gcc-13 -o mainc main.c -pedantic -Wall -Wextra
./mainc
