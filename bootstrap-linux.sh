#!/bin/bash

# Copyright (c) 2008-2020, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

rm -rf build.linux
mkdir build.linux
cd build.linux

cmake . \
      -DCMAKE_BUILD_TYPE=Debug \
      -G"Unix Makefiles" \
      -Wno-dev \
      ..

make
