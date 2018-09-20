mkdir build_debug
cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
read -n1 -r -p "Press any key to continue..." key