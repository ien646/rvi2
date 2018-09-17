md build_release
cd build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
pause