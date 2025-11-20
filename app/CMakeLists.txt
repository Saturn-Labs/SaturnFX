cmake_minimum_required(VERSION 3.20)
project(app)
set(CMAKE_CXX_STANDARD 23)

include_directories(
        ${CMAKE_SOURCE_DIR}/saturnfx/include
)

file(GLOB_RECURSE APP_INCLUDE_LIST
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE APP_SOURCE_LIST
        "${SOURCE_DIR}/*.cpp"
)

add_executable(app
        ${APP_INCLUDE_LIST}
        ${APP_SOURCE_LIST}
)

target_precompile_headers(app PRIVATE "${SOURCE_DIR}/pch.hpp")
target_link_libraries(app
        PRIVATE
        saturnfx
)