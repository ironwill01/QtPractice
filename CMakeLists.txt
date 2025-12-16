# This part is optional but lets define it anyway

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    IWCLOCK
    VERSION 1.0.0
    LANGUAGES CXX C
)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(LIB_NAME_INCLUDE ClockIncludes)
set(LIB_NAME ClockLib)
set(EXE_NAME QClockApp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeMods")

include(Addall)

add_subdir_list(app libs)
