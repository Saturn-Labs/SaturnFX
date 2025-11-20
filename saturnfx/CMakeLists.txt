cmake_minimum_required(VERSION 3.20)
project(saturnfx)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
        ${INCLUDE_DIR}
        ${SOURCE_DIR}
)

file(GLOB_RECURSE API_INCLUDE_LIST
        "${INCLUDE_DIR}/*.h"
        "${INCLUDE_DIR}/*.hpp"
)

file(GLOB_RECURSE INCLUDE_LIST
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE SOURCE_LIST
        "${SOURCE_DIR}/*.cpp"
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory("${EXTERNAL_DIR}/glfw" "${CMAKE_CURRENT_BINARY_DIR}/glfw")
add_subdirectory("${EXTERNAL_DIR}/glad" "${CMAKE_CURRENT_BINARY_DIR}/glad")
add_subdirectory("${EXTERNAL_DIR}/spdlog" "${CMAKE_CURRENT_BINARY_DIR}/spdlog")

add_library(saturnfx STATIC
        ${API_INCLUDE_LIST}
        ${INCLUDE_LIST}
        ${SOURCE_LIST}
)
target_include_directories(saturnfx
        PUBLIC
        ${INCLUDE_DIR}
)
target_link_libraries(saturnfx
        PUBLIC
        glfw
        glad
        spdlog::spdlog
)

target_compile_definitions(saturnfx
        PUBLIC
        $<$<CONFIG:Debug>:DEBUG>
        GLFW_INCLUDE_NONE
)

target_precompile_headers(saturnfx PUBLIC "${SOURCE_DIR}/pch.hpp")