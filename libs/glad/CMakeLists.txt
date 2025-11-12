cmake_minimum_required(VERSION 4.0)
project(glad LANGUAGES C)

add_library(glad STATIC
        src/gl.c
)

target_include_directories(glad
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# On some systems you also need to link to dl (for dlsym)
if(UNIX AND NOT APPLE)
    target_link_libraries(glad PRIVATE dl)
endif()

# Provide an alias target for modern usage
add_library(glad::glad ALIAS glad)
