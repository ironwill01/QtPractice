add_library(
    ${LIB_NAME_INCLUDE} INTERFACE
)

file(GLOB_RECURSE INCLUDE_DIRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/**/*.hpp")

set(INCLUDE_REAL_DIRS "")

foreach(include_hpp ${INCLUDE_DIRS})
    get_filename_component(dir ${include_hpp} DIRECTORY)
    list(APPEND INCLUDE_REAL_DIRS ${dir})
endforeach()

list(REMOVE_DUPLICATES INCLUDE_REAL_DIRS)

target_include_directories(
    ${LIB_NAME_INCLUDE}
        PUBLIC
            ${INCLUDE_REAL_DIRS}
)

target_link_libraries(
    ${LIB_NAME_INCLUDE}
        INTERFACE
            Qt6::Core
)