rmdir build /s /q
md build
cd build
cmake ..
cmake --build .

move output ..\__temp
cd ..
rmdir build /s /q
md build
cd build
move ..\__temp output

echo "FINISHED!"
pause
