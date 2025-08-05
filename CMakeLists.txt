cmake_minimum_required(VERSION 3.10)

project(RayTracing VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(glm CONFIG REQUIRED)

add_executable(RayTracing src/main.cpp)

target_include_directories(RayTracing
    PRIVATE
    ./include
)

target_link_libraries(RayTracing
    PRIVATE
    glm::glm-header-only
)
