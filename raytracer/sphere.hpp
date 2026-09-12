#pragma once

#include <iostream>
#include "math/vec3.hpp"
#include "raytracer/ray.hpp"

double hitsphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto d = r.direction();
    auto a = dot(d,d);
    auto b = -2*(dot(d,oc));
    auto c = dot(oc,oc) - radius*radius;
    auto disc = b*b - 4*a*c;  
    if(disc>=0){
        auto t_min = -b-sqrt(disc); // nearer t
        auto t_max = -b+sqrt(disc);  //far t
        
        if (t_min >= 0){      //if t_min  was negative, then it is intersecting behind the camera(the origin point is taken as camera thats why)
            return t_min/(2.0*a);
        }
        else{
            return t_max/(2.0*a);  //if this was also negative, then both of them are intersecting behind the camera
        }
        
    }
    else{
        return -1.0; // if disc < 0 then intersection is not possible
    }
}


