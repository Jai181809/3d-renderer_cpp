# 3D Renderer (C++)

A ray tracer built from scratch in C++, following *Ray Tracing in One Weekend* (with some additions of my own).
## What it does

Renders scenes using ray tracing, outputting a PPM image (auto-converted to PNG). Currently supports:
- Camera/viewport setup with configurable aspect ratio and image width
- Ray generation per pixel
- Background gradient sky

![Sample render](3d-renderer/build/image.png)

## Building

\`\`\`bash
mkdir build && cd build
cmake ..
make
\`\`\`

## Running

\`\`\`bash
./3d-renderer
\`\`\`
Outputs `image.ppm`, converts it to `image.png`, and opens it automatically.

## Structure

- `raytracer/` — camera and rendering logic
- `math/` — vector math (vec3, point3)
- `src/` — color handling, image I/O