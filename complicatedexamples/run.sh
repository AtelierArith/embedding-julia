# Get Julia installation paths
rm -rf build
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --config Release -j `nproc`
./build/main
