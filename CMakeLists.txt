cmake_minimum_required(VERSION 3.19)
project(brot VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(brot-parser INTERFACE)
target_compile_features(brot-parser INTERFACE cxx_std_20)
target_compile_options(brot-parser INTERFACE -fno-exceptions -fno-rtti)
target_include_directories(brot-parser INTERFACE inc)
target_include_directories(brot-parser INTERFACE ext/m4c0-stl/parser/inc)

add_executable(brot-cat src/cat.cpp)
target_link_libraries(brot-cat PUBLIC brot-parser)

add_executable(brot-expand src/expand.cpp)
target_link_libraries(brot-expand PUBLIC brot-parser)
