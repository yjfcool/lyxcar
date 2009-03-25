#!/bin/sh

if [ ! -f ./lyxcar ]; then
   echo "Compile first (qmake; make)"
   exit 1
fi

export LD_LIBRARY_PATH=./:~/local/lib64
./lyxcar
