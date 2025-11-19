cmake_minimum_required(VERSION 3.20)

project(saturnfx)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR "src")
set(INCLUDE_DIR "inc")
set(EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/external")

add_subdirectory("saturnfx")
add_subdirectory("app")
