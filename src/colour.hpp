#pragma once

#include <iostream>
#include <cmath>
#include <cstdint>
#include "interval.hpp"

using namespace std;

using colour = vec3;

inline void write_color(ostream& out, const colour& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static const interval intensity(0.000, 0.999);

    // Clamp and scale to 8-bit unsigned integer range (0 - 255)
    uint8_t rbyte = static_cast<uint8_t>(256 * intensity.clamp(r));
    uint8_t gbyte = static_cast<uint8_t>(256 * intensity.clamp(g));
    uint8_t bbyte = static_cast<uint8_t>(256 * intensity.clamp(b));

    // Write exact binary bytes to stream (no spaces, no newlines)
    out.put(static_cast<char>(rbyte));
    out.put(static_cast<char>(gbyte));
    out.put(static_cast<char>(bbyte));
}