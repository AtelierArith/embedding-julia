# Get Julia installation paths
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --config Release -j `nproc`
./build/hello
