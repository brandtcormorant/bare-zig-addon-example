cmake_minimum_required(VERSION 3.25)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_addon C)

add_bare_module(bare_addon)

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

target_include_directories(${bare_addon}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
 )

target_link_libraries(${bare_addon}
  PRIVATE
    libbare_zig_example
 )

target_sources(
  ${bare_addon}
  PRIVATE
    binding.c
)
