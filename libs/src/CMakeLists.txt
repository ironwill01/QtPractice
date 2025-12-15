file(GLOB_RECURSE SRC_DIRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp")
file(GLOB_RECURSE HEADER_DIRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../includes/**/*.hpp")

add_library(
    ${LIB_NAME}
        STATIC
            ${SRC_DIRS}
            ${HEADER_DIRS}
)

set_target_properties(
    ${LIB_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_include_directories(
    ${LIB_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../includes
)

target_link_libraries(
    ${LIB_NAME}
        PUBLIC
            ${LIB_NAME_INCLUDE}
            Qt6::Core
)