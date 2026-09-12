#pragma once

#include <iostream>
#include <cmath>
#include "math/vec3.hpp"
using namespace std;
using colour = vec3;

inline void write_color(ostream& out, const colour& pixel_color) {  //here we pass ostream& so that we can save and print both, while also giving us flexibility over other ostream components
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    int rbyte = (255.999*r);  // using this to normalize the values to be between 0-255
    int gbyte = (255.999*g);
    int bbyte = (255.999*b);  
    out << rbyte << " " << gbyte << " " << bbyte << "\n";
    
}
