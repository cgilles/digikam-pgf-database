#
# Copyright (c) 2010-2021 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(digikam-pgf-database)

cmake_minimum_required(VERSION "3.3.2")

find_package(Qt5 5.6.0
             NO_MODULE COMPONENTS
             Core
             Gui
)

include_directories(pgfutils/
                    pgfutils/libpgf/
)

add_executable(pgfdatabase
               loadpgfblob.cpp
               pgfutils/pgfutils.cpp
               pgfutils/libpgf/Decoder.cpp
               pgfutils/libpgf/Encoder.cpp
               pgfutils/libpgf/PGFimage.cpp
               pgfutils/libpgf/PGFstream.cpp
               pgfutils/libpgf/Subband.cpp
               pgfutils/libpgf/WaveletTransform.cpp
)

target_link_libraries(pgfdatabase
                      Qt5::Core
                      Qt5::Gui
)
