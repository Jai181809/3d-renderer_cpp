cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer src/main.cpp)

find_program(MAGICK_EXECUTABLE magick)

if (MAGICK_EXECUTABLE)
    add_custom_target(render_and_convert ALL
        COMMAND raytracer
        COMMAND ${MAGICK_EXECUTABLE} image.ppm image.png
        DEPENDS raytracer
        COMMENT "Rendering raytracer to PPM and converting to PNG..."
    )
endif()