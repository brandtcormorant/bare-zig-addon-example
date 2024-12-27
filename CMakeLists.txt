cmake_minimum_required(VERSION 3.25)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_zig_example C)

add_bare_module(bare_zig_example)

add_library(libbare_zig_example STATIC IMPORTED)

target_include_directories(${bare_zig_example}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
 )

target_link_libraries(${bare_zig_example}
  PRIVATE
    libbare_zig_example
 )

target_sources(
  ${bare_zig_example}
  PRIVATE
    binding.c
)
