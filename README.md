# RVI2
Rain Vectorial Interface

[![Total alerts](https://img.shields.io/lgtm/alerts/g/bigiansen/rvi2.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/bigiansen/rvi2/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/bigiansen/rvi2.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/bigiansen/rvi2/context:cpp)

[![Build Status](https://amsostudios.visualstudio.com/rvi2/_apis/build/status/RVI2-CI?branchName=master)](https://amsostudios.visualstudio.com/rvi2/_build/latest?definitionId=2?branchName=master)

## Build requirements
 - Git (submodule dependencies)
 - Relatively up-to-date CMake
 - C++17 compatible compiler (might require editing CMakeLists.txt)
##### Tested compilers:
    - [x86] MSVC v14.1 (Visual Studio 2017)
    - [ARM] GNU GCC 7.3.0
##### Theoretically supported compilers:
	- GNU GCC > 7.X
	- CLANG > 6
	- MSVC > v14.0 (Visual Studio 2015 and later)

### OS Specific requirements:
##### Linux:
 - For building Cozy: libX11 (xorg, xorg-dev)