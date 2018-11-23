git submodule update --init
mkdir build_release
cd build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
read -n1 -r -p "Press any key to continue..." key