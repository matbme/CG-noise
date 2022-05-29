cmake_minimum_required(VERSION 3.10)

# Modules path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules")

# Generate file for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(CGnoise)

# All source files
file(GLOB SRC_FILES src/*.cpp)
file(GLOB SRC_FILES_C src/*.c)

add_executable(app ${SRC_FILES} ${SRC_FILES_C})

# C++17 standard
set_target_properties(app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
)

find_package(LibNoise REQUIRED)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lnoise")

target_link_libraries(app noiseutils-static)
