cmake_minimum_required(VERSION 3.20.0)
project(kptdupa VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(axxegro)

add_executable(kptdupa src/main.cpp)
target_link_libraries(kptdupa PRIVATE axxegro)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
