#!/bin/bash

script="`readlink -f "${BASH_SOURCE[0]}"`"
CALLDIR="`dirname "$script"`"
cd ${CALLDIR}

qmake CONFIG+=debug RRAMSpec.pro
echo "Compiling..."
sleep 0.1
make -s -j 16

echo "Testing..."
cd build/debug/
./rramspec_test
