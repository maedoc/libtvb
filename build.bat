mkdir cmake_build

cd cmake_build

cmake -G "MinGW Makefiles" ..

make -j

cd test

ctest
