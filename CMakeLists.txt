cmake_minimum_required(VERSION 3.10)
project(RayTracer) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer src/main.cpp
    src/Image_opener.hpp
    src/Image_opener.cpp)

find_program(MAGICK_EXECUTABLE magick)


