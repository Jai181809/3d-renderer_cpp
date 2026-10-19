cmake_minimum_required(VERSION 3.10)
project(3D-Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to an optimized build unless the user chose one
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(3d-renderer main.cpp
    src/Image_opener.hpp
    src/Image_opener.cpp
    Math/vec3.cpp
    src/colour.hpp
    raytracer/ray.hpp
    raytracer/camera.hpp
    objects/sphere.hpp
    raytracer/hittable.hpp
    raytracer/hittable_list.hpp
    Math/constants.hpp          # lowercase to match math/vec3.cpp
    objects/Triangle.hpp
    objects/ob.hpp
    objects/poly.hpp
    header_files.hpp)

target_include_directories(3d-renderer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_program(MAGICK_EXECUTABLE magick)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(3d-renderer PRIVATE OpenMP::OpenMP_CXX)
endif()