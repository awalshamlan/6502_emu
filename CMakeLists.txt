cmake_minimum_required(VERSION 3.20)

project(M6502Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE M6502_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/M6502Lib/src/*.cpp"
)

add_library(M6502Lib
    ${M6502_SOURCES}
)

target_include_directories(M6502Lib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/M6502Lib/include"
)

enable_testing()
add_subdirectory(tests)