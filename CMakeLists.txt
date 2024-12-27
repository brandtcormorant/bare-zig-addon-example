cmake_minimum_required(VERSION 3.25)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_zig_example C)

add_bare_module(bare_zig_example)

if(target MATCHES "win32")
  add_compile_options(/MT$<$<CONFIG:Debug>:d>)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()

add_library(libbare_zig_example STATIC IMPORTED)

if(WIN32)
    set_target_properties(libbare_zig_example PROPERTIES
        IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/zig-out/lib/bare_zig_example.lib"
    )
else()
    set_target_properties(libbare_zig_example PROPERTIES
        IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/zig-out/lib/libbare_zig_example.a"
    )
endif()

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
