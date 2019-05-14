echo "-- Initializing git submodules -- "
git submodule update --init --recursive
mkdir build_release_linux
cd build_release_linux
cmake -DCMAKE_BUILD_TYPE=Release .. -Wdev
cmake --build . --config Release
read -n1 -r -p "Press any key to continue..." key