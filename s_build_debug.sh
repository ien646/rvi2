echo "-- Initializing git submodules -- "
git submodule update --init
mkdir build_debug
cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug .. -Wdev
cmake --build . --config Debug
read -n1 -r -p "Press any key to continue..." key