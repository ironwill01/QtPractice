file(GLOB_RECURSE SRC_DIRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp")

add_library(
    ${LIB_NAME}
        STATIC
            ${SRC_DIRS}
)

set_target_properties(
    ${LIB_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_link_libraries(
    ${LIB_NAME}
        PUBLIC
            ${LIB_NAME_INCLUDE}
)