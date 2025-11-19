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
set_target_properties(
        app
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/app/${CMAKE_BUILD_TYPE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/app/${CMAKE_BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/app/${CMAKE_BUILD_TYPE}
)

add_custom_command(
        TARGET app
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_SOURCE_DIR}/output/app/${CMAKE_BUILD_TYPE}/assets
        COMMENT "Assets copied to output folder."
)