cmake_minimum_required(VERSION 3.20)
project(Hello LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
find_package(Julia REQUIRED)

add_executable(hello main.c)
target_include_directories(hello PUBLIC ${Julia_INCLUDE_DIRS})
target_link_libraries(hello ${Julia_LIBRARY})
