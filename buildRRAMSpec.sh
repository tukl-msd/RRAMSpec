#!/bin/bash

script="`readlink -f "${BASH_SOURCE[0]}"`"
CALLDIR="`dirname "$script"`"
cd ${CALLDIR};

qmake CONFIG+=release RRAMSpec.pro
echo "Compiling..."
sleep 0.1
make -s
echo "Ready!"
