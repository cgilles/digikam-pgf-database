#
# SPDX-FileCopyrightText: 2010-2026, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# SPDX-License-Identifier: BSD-3-Clause

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
               pgfutils/digikam_debug.cpp
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
