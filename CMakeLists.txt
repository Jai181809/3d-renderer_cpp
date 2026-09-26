cmake_minimum_required(VERSION 3.10)
project(3D-Renderer) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3d-renderer main.cpp
    src/Image_opener.hpp
    src/Image_opener.cpp
    math/vec3.cpp
    src/colour.hpp
    raytracer/ray.hpp
    raytracer/camera.hpp
    raytracer/sphere.hpp
    raytracer/hittable.hpp
    raytracer/hittable_list.hpp
    Math/constants.hpp)

target_include_directories(3d-renderer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_program(MAGICK_EXECUTABLE magick)


