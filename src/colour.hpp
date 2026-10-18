#pragma once

#include <iostream>
#include <cmath>
#include "interval.hpp"

using namespace std;

using colour = vec3;

inline void write_color(ostream& out, const colour& pixel_color) {  //here we pass ostream& so that we can save and print both, while also giving us flexibility over other ostream components
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static const interval intensity(0.000, 0.999);
    int rbyte = (256*intensity.clamp(r));  // using this to normalize the values to be between 0-255
    int gbyte = (256*intensity.clamp(g));
    int bbyte = (256*intensity.clamp(b));  
    out << rbyte << " " << gbyte << " " << bbyte << "\n";
    
}
