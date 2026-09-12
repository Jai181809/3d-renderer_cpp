#pragma once

#include <iostream>
#include "math/vec3.hpp"
#include "raytracer/ray.hpp"

bool hitsphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto d = r.direction();
    auto a = dot(d,d);
    auto b = -2*(dot(d,oc));
    auto c = dot(oc,oc) - radius*radius;
    auto disc = b*b - 4*a*c;  //discriminant
    return (disc >= 0);
}


