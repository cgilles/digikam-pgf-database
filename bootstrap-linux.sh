#!/bin/bash

# SPDX-FileCopyrightText: 2008-2026 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# SPDX-License-Identifier: BSD-3-Clause

rm -rf build.linux
mkdir build.linux
cd build.linux

cmake . \
      -DCMAKE_BUILD_TYPE=Debug \
      -G"Unix Makefiles" \
      -Wno-dev \
      ..

make
