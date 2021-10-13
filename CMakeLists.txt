cmake_minimum_required(VERSION 3.19)
project(brot VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(brot-parser INTERFACE)
target_compile_features(brot-parser INTERFACE cxx_std_20)
target_compile_options(brot-parser INTERFACE -fno-exceptions -fno-rtti)
target_include_directories(brot-parser INTERFACE inc)
target_include_directories(brot-parser INTERFACE
  ext/m4c0-stl/units/inc
  ext/m4c0-stl/parser/inc
  )

function(brot_tool NAME)
  add_executable(brot-${NAME} src/${NAME}.cpp)
  target_link_libraries(brot-${NAME} PUBLIC brot-parser)
endfunction()

brot_tool(cat)
brot_tool(expand)
brot_tool(jlcpcb-bom)
brot_tool(jlcpcb-pnp)
