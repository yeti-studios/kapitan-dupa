cmake_minimum_required(VERSION 3.20.0)
project(kptdupa VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(axxegro)

file(GLOB_RECURSE KPTDUPA_SOURCES "src/*.cpp")
file(GLOB_RECURSE KPTDUPA_HEADERS "src/*.hpp")

add_executable(kptdupa ${KPTDUPA_SOURCES} ${KPTDUPA_HEADERS})
target_link_libraries(kptdupa PRIVATE axxegro)

find_package(nlohmann_json REQUIRED)
target_link_libraries(kptdupa PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(TARGET kptdupa POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/res
)



set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
