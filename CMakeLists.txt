# Space64 - N64 Game CMake Configuration
# This wraps the libdragon Makefile build system
#
# IMPORTANT: libdragon uses Makefiles natively, not CMake.
# This CMakeLists.txt provides IDE integration (autocomplete, indexing)
# but the actual build uses the Makefile via build_game.bat

cmake_minimum_required(VERSION 3.20)
project(space64 C)

# N64 toolchain paths (adjust if needed)
set(N64_INST "c:/n64-toolchain")
set(T3D_INST "${CMAKE_SOURCE_DIR}/tiny3d")

# Include paths for IDE autocomplete/indexing
set(INCLUDE_DIRS
    ${N64_INST}/mips64-elf/include
    ${T3D_INST}/src
    ${CMAKE_SOURCE_DIR}/src
)

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.c"
    "src/*.h"
)

# This is a "fake" executable for IDE support
# The actual build happens via Makefile
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Definitions for IDE (matches libdragon)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    N64
    _MIPS_SZLONG=32
    _MIPS_SZINT=32
)

# Custom build commands that use the real Makefile
add_custom_target(build_rom
    COMMAND ${CMAKE_SOURCE_DIR}/build_game.bat
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building N64 ROM via libdragon Makefile"
)

add_custom_target(clean_rom
    COMMAND ${CMAKE_SOURCE_DIR}/clean.bat
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Cleaning build artifacts"
)

# Prevent CMake from trying to actually compile (it can't cross-compile for N64)
set_target_properties(${PROJECT_NAME} PROPERTIES
    EXCLUDE_FROM_ALL TRUE
    EXCLUDE_FROM_DEFAULT_BUILD TRUE
)
