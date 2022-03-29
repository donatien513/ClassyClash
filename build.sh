#!/bin/bash
g++ main.cpp -o classy_clash -std=c++17 -ferror-limit=1000 -I./raylib/include -L./raylib/lib -lraylib -Wl,-rpath,"raylib/lib" -g

# if Mac M1
# arch -x86_64 ./build.sh

# else (linux, windows)
# ./build.sh
