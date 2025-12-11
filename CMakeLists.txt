# Specific setting for QT part 

if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "C++ compiler" FORCE)
endif()

if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "clang" CACHE STRING "C compiler" FORCE)
endif()

# This part is optional but lets define it anyway

set(QT_QMAKE_TARGET_MKSPEC "linux-clang-qt6" CACHE STRING "" FORCE)

# Generic settings

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Naming components of the project

set(EXE_NAME IWCLOCK)
set(LIB_NAME IWLIB)
set(LIB_NAME_INCLUDE ${LIB_NAME}_INCLUDE)

project(
    IWCLOCK
    VERSION 1.0.0
    LANGUAGES CXX C
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeMods")

include(Addall)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

set(
    ROOT_DIRS
    libs
    app
)

# Custom made function

add_subdir_list(${ROOT_DIRS})