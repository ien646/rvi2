rm build -r
mkdir build
cd build
cmake ..
cmake --build .

mv output ../__temp
cd ..
rm build -r
mkdir build
cd build
mv ../__temp output

echo "PRESS ANY KEY TO EXIT..."
read -n 1