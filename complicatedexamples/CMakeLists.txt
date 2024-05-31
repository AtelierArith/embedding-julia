cmake_minimum_required(VERSION 3.20)
project(ComplicatedExample)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
find_package(Julia REQUIRED)

add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_11)
target_include_directories(main PUBLIC ${Julia_INCLUDE_DIRS})
target_link_libraries(main ${Julia_LIBRARY})
