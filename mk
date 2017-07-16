#!/bin/bash

#MFILE="main.cc record.cc table.cc"

function mkdebug() {
  c++ -std=c++11 -Wall -Wextra -Wno-sign-compare -g $MFILE #"string.cpp" #|tee log
}

function make() {
  c++ -std=c++11 -Wl,--gc-sections -fno-asynchronous-unwind-tables -Wl,--strip-all -Wall -Wextra -Wno-sign-compare $MFILE #"string.cpp" #|tee log
}

if [[ "x$1" == "xr" ]]; then
  make
elif [[ "x$1" == "xb" ]]; then
  if [[ ! -d backup ]]; then mkdir backup; fi
  find *.{cc,h}|cpio -o|xz -z >"backup/$(date +'%j%Y%H%M%S').cpio.xz"
elif [[ "x$1" == "xd" ]]; then
  mkdebug
  echo "compiling...done. run"
  gdb -q ./a.out
elif [[ "x$1" == "xc" ]]; then
  mkdebug
  valgrind -v --time-stamp=yes --leak-resolution=high --show-leak-kinds=all --track-origins=yes --log-file=summary/summary-$(date +'%j%Y%H%M%S') --leak-check=full --leak-check-heuristics=all ./a.out
else mkdebug
fi

