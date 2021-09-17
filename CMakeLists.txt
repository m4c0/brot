cmake_minimum_required(VERSION 3.19)
project(brot VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(brot-cat src/cat.cpp)
target_compile_features(brot-cat PUBLIC cxx_std_20)
target_include_directories(brot-cat PUBLIC inc)
target_include_directories(brot-cat PUBLIC ext/m4c0-stl/parser/inc)
