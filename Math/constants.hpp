#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


#include "src/colour.hpp"
#include "raytracer/ray.hpp"
#include "vec3.hpp"


using namespace std;

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
