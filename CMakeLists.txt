cmake_minimum_required(VERSION 3.25.1)
project(Kuiper VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/entity
    ${PROJECT_SOURCE_DIR}/include/gui
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/entity
    ${PROJECT_SOURCE_DIR}/src/gui
)

# Find SFML shared libraries
find_package(SFML 2.5...<3.0 COMPONENTS system window graphics audio REQUIRED)

file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/include/entity/*.hpp"
    "${PROJECT_SOURCE_DIR}/include/gui/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/entity/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/*.cpp"
)

add_executable(Kuiper ${SRCS})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-graphics sfml-system sfml-audio)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)
add_dependencies(Kuiper copy_assets)
