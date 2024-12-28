cmake_minimum_required(VERSION 3.27)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_addon C)

add_bare_module(bare_addon)

target_include_directories(${bare_addon}
    PUBLIC
        include
)

add_library(zig_lib OBJECT IMPORTED)

if(WIN32)
    set(OBJ_SUFFIX ".obj")
    
    target_link_libraries(
    ${bare_addon}
    PRIVATE
        ntdll
)

else()
    set(OBJ_SUFFIX ".o")
endif()

set_target_properties(zig_lib PROPERTIES
    IMPORTED_OBJECTS "${CMAKE_CURRENT_SOURCE_DIR}/zig-out/lib/bare_zig_example${OBJ_SUFFIX}"
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
