#!/bin/bash
g++ main.cpp -o classy_clash -I./raylib/include -L./raylib/lib -lraylib -Wl,-R./raylib/lib
