#!/bin/bash
find $1 -iname "*.h" -o -iname "*.c" -o -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -i -verbose
