cmake_minimum_required(VERSION 3.18)

cmake_policy(SET CMP0135 NEW)

project(URI LANGUAGES C CXX)
set(CMAKE_C_STANDARD 23)

add_library(uri STATIC uri.c)

target_include_directories(uri PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(uri_tests main.c)

target_link_libraries(uri_tests PRIVATE uri)