#
# SPDX-FileCopyrightText: 2010-2026, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# SPDX-License-Identifier: BSD-3-Clause

project(digikam-pgf-database)

cmake_minimum_required(VERSION "3.16")

if(BUILD_WITH_QT6)

    set(QT6_MIN_VERSION 6.2)
    set(QT_DEFAULT_MAJOR_VERSION 6)
    find_package(Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS Core Gui)

    set(QT_VERSION       ${Qt6Core_VERSION})
    set(QT_MIN_VERSION   ${QT6_MIN_VERSION})
    set(QT_VERSION_MAJOR 6)

else()

    set(QT5_MIN_VERSION 5.6)
    set(QT_DEFAULT_MAJOR_VERSION 5)
    find_package(Qt5 ${QT5_MIN_VERSION} REQUIRED COMPONENTS Core Gui)

    set(QT_VERSION       ${Qt5Core_VERSION})
    set(QT_MIN_VERSION   ${QT5_MIN_VERSION})
    set(QT_VERSION_MAJOR 5)

endif()

message(STATUS "Suitable Qt${QT_VERSION_MAJOR} >= ${QT_MIN_VERSION} detected: '${QT_VERSION}'.")

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
                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Gui
)
