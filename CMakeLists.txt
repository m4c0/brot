cmake_minimum_required(VERSION 3.19)
project(brot VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(ext/m4c0-stl)

add_executable(brot-cat src/cat.cpp)
target_compile_features(brot-cat PUBLIC cxx_std_20)
target_link_libraries(brot-cat PUBLIC m4c0::parser)
