cmake_minimum_required(VERSION 3.27)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_addon C)

add_bare_module(bare_addon)

target_include_directories(${bare_addon}
    PUBLIC
        include
)

add_library(zig_lib OBJECT IMPORTED)
set_target_properties(zig_lib PROPERTIES
    IMPORTED_OBJECTS "${CMAKE_CURRENT_SOURCE_DIR}/zig-out/lib/bare_zig_example.o"
)

target_sources(
    ${bare_addon}
    PRIVATE
        binding.c
)

target_link_libraries(
    ${bare_addon}
    PRIVATE
        $<TARGET_OBJECTS:zig_lib>
)