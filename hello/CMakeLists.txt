set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Julia REQUIRED)

add_executable(hello hello.cpp)
target_compile_features(hello PUBLIC cxx_std_11)
target_include_directories(hello PUBLIC ${Julia_INCLUDE_DIRS})
target_link_libraries(hello ${Julia_LIBRARY})
