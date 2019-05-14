echo "-- Initializing git submodules -- "
git submodule update --init --recursive
mkdir build_debug_linux
cd build_debug_linux
cmake -DCMAKE_BUILD_TYPE=Debug .. -Wdev
cmake --build . --config Debug
read -n1 -r -p "Press any key to continue..." key