cmake_minimum_required(VERSION 3.20)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(raytracer_lib
    src/common.cc
    src/vec3.cc
    src/color.cc
    src/sphere.cc
    src/hittable_list.cc
    src/camera.cc
)

target_include_directories(raytracer_lib PUBLIC include)

add_executable(raytracer src/main.cc)
target_link_libraries(raytracer PRIVATE raytracer_lib)
