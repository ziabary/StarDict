StarDict
========

A C++ library to read Stardict file directly derived from http://code.google.com/p/stardict-3/

## Build and test:

Dependencies:
 * GCC (+4.8)
 * Make or any IDE supported by CMake (Visual Studio, Eclipse, XCode, KDevelop, etc)


#### Configure and generate build files:

    mkdir -p $StarDict/build
    cd $StarDict/build
    cmake -DCMAKE_INSTALL_PREFIX:PATH=~/local ..

#### Build:

    cd $StarDict/build
    make

#### Run the tests:

    cd $StarDict/build/test
    ./test
