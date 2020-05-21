#!/bin/bash

# Script to build a bundle MXE static installation in a dedicated directory.
#
# Copyright (c) 2015-2020 by Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# Halt and catch errors
set -eE
trap 'PREVIOUS_COMMAND=$THIS_COMMAND; THIS_COMMAND=$BASH_COMMAND' DEBUG
trap 'echo "FAILED COMMAND: $PREVIOUS_COMMAND"' ERR

#################################################################################################
# Manage script traces to log file

mkdir -p ./logs
exec > >(tee ./logs/build-mxe.full.log) 2>&1

#################################################################################################

echo "build-mxe.sh : build a bundle MXE install with Exiv2 dependencies."
echo "-----------------------------------------------------------------------"

#################################################################################################
# Configuration

# Absolute path where are downloaded all tarballs to compile.
DOWNLOAD_DIR="`pwd`/temp.dwnld"

# Absolute path where are compiled all tarballs
BUILDING_DIR="`pwd`/temp.build"

#-------------------------------------------------------------------------------------------

# MXE configuration

#------------
# IMPORTANT: Target Windows architecture to build installer. Possible values: 32 or 64 bits.
MXE_ARCHBITS=64
#------------

if [[ $MXE_ARCHBITS == 32 ]]; then
    # Windows 32 bits static
    MXE_BUILD_TARGETS="i686-w64-mingw32.static"
    MXE_BUILDROOT="`pwd`/build.win32"
elif [[ $MXE_ARCHBITS == 64 ]]; then
    # Windows 64 bits static
    MXE_BUILD_TARGETS="x86_64-w64-mingw32.static"
    MXE_BUILDROOT="`pwd`/build.win64"
else
    echo "Unsupported or wrong target Windows architecture: $MXE_ARCHBITS bits."
    exit -1
fi

echo "Target Windows architecture: $MXE_ARCHBITS bits."

MXE_GIT_URL="https://github.com/mxe/mxe.git"
MXE_GIT_REVISION=master
MXE_INSTALL_PREFIX=${MXE_BUILDROOT}/usr/${MXE_BUILD_TARGETS}/
MXE_TOOLCHAIN=${MXE_INSTALL_PREFIX}/share/cmake/mxe-conf.cmake

#################################################################################################
# Macro definitions

ChecksCPUCores()
{
CPU_CORES=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || sysctl -n hw.ncpu)

if [[ $CPU_CORES -gt 1 ]]; then
    CPU_CORES=$((CPU_CORES-1))
fi

echo "CPU Cores to use : $CPU_CORES"
}

# For time execution measurement ; startup
StartScript()
{
BEGIN_SCRIPT=$(date +"%s")
}

# For time execution measurement : shutdown
TerminateScript()
{
TERMIN_SCRIPT=$(date +"%s")
difftimelps=$(($TERMIN_SCRIPT-$BEGIN_SCRIPT))
echo "Elaspsed time for script execution : $(($difftimelps / 3600 )) hours $((($difftimelps % 3600) / 60)) minutes $(($difftimelps % 60)) seconds"
}

#################################################################################################

StartScript
ChecksCPUCores

# Pathes rules
ORIG_PATH="$PATH"
ORIG_WD="`pwd`"

export PATH=$MXE_BUILDROOT/usr/bin:$MXE_INSTALL_PREFIX/qt5/bin:$PATH

#################################################################################################
# Check if a previous bundle already exist

CONTINUE_INSTALL=0

if [ -d "$MXE_BUILDROOT" ] ; then

    read -p "$MXE_BUILDROOT already exist. Do you want to remove it or to continue an aborted previous installation ? [(r)emove/(c)ontinue/(s)top] " answer

    if echo "$answer" | grep -iq "^r" ;then

        echo "---------- Removing existing $MXE_BUILDROOT"
#        chmod +w "$MXE_BUILDROOT/usr/readonly"
#        chattr -i "$MXE_BUILDROOT/usr/readonly/.gitkeep"
        rm -rf "$MXE_BUILDROOT"

    elif echo "$answer" | grep -iq "^c" ;then

        echo "---------- Continue aborted previous installation in $MXE_BUILDROOT"
        CONTINUE_INSTALL=1

    else

        echo "---------- Aborting..."
        exit;

    fi

fi

if [[ $CONTINUE_INSTALL == 0 ]]; then

    # Checkout latest MXE from github
    git clone $MXE_GIT_URL $MXE_BUILDROOT

fi

#################################################################################################
# MXE git revision to use

cd $MXE_BUILDROOT

if [[ $MXE_GIT_REVISION == "master" ]]; then
    echo -e "\n"
    echo "---------- Updating MXE"
    git pull
else
    echo -e "\n"
    echo "---------- Checkout MXE revision to $MXE_GIT_REVISION"
    git checkout $MXE_GIT_REVISION
fi

#################################################################################################
# Dependencies build and installation

# Use a more recent gcc version with MXE
echo -e "\n"
echo "---------- Building cross-compiler for MXE"
make MXE_TARGETS=$MXE_BUILD_TARGETS cc MXE_PLUGIN_DIRS="plugins/gcc9" 

# Switch to a more recent gcc version
echo 'override MXE_PLUGIN_DIRS += plugins/gcc9' >> settings.mk

make MXE_TARGETS=$MXE_BUILD_TARGETS \
     cmake \
     qtbase

echo -e "\n"

cd $ORIG_WD
mkdir -p build.mxe
cd build.mxe

#################################################################################################

${MXE_BUILD_TARGETS}-cmake .. \
                           -DMXE_TOOLCHAIN=${MXE_TOOLCHAIN} \
                           -DMXE_BUILDROOT=${MXE_BUILDROOT} \
                           -DMXE_ARCHBITS=${MXE_ARCHBITS} \
                           -DMXE_INSTALL_PREFIX=${MXE_INSTALL_PREFIX} \
                           -DCMAKE_BUILD_TYPE=RelWithDebInfo \
                           -DCMAKE_COLOR_MAKEFILE=ON \
                           -DCMAKE_TOOLCHAIN_FILE=${MXE_TOOLCHAIN} \
                           -DCMAKE_FIND_PREFIX_PATH=${CMAKE_PREFIX_PATH} \
                           -DCMAKE_SYSTEM_INCLUDE_PATH=${CMAKE_PREFIX_PATH}/include \
                           -DCMAKE_INCLUDE_PATH=${CMAKE_PREFIX_PATH}/include \
                           -DCMAKE_LIBRARY_PATH=${CMAKE_PREFIX_PATH}/lib \
                           -DZLIB_ROOT=${CMAKE_PREFIX_PATH}


${MXE_BUILD_TARGETS}-cmake --build .

export PATH=$ORIG_PATH

TerminateScript
