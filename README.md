This small program is a simple converter to procress digiKam database thumbnails image to PNG.

digiKam store thumbnails with wavelets PGF codec to reduce size with a very good quality.

To compile this code, you need Cmake and Qt5 Core and Gui modules under Linux. There is no dependency to digiKam core.
To compile this code from Windows, You need to solve dependencies for MXE cross compiler.

Two scripts are provided to compile under linux (bootstrap-linux.sh) and cross compile to Windows using MXE (bootstrap-mxe.sh).

To convert blob data from digiKam database, just pass the binary file to the cli tool. It will convert to PNG image.

Links:

Cmake  : https://cmake.org/
Qt5    : https://www.qt.io/
MXE    : https://mxe.cc/
digiKam: https://www.digikam.org/
