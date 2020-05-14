@ECHO OFF

REM Manage build sub-dir.
rmdir /q /s "build"
md "build"
cd "build"

REM Customize Qt5 install path
set Qt5_DIR=C:\Qt5

REM Microsoft Visual C++ command line compiler.
cmake -G "NMake Makefiles" . 
      -DCMAKE_BUILD_TYPE=Debug 
      -DCMAKE_PREFIX_PATH=%Qt5_DIR% 
      -Wno-dev 
      ..

