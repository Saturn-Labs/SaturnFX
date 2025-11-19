cmake_minimum_required(VERSION 3.20)

add_library(glad STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
)

target_include_directories(glad
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(UNIX AND NOT APPLE)
    target_link_libraries(glad PUBLIC dl)
endif()
