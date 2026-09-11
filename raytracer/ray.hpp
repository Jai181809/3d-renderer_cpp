#pragma once

#include <iostream>
#include "math/vec3.hpp"

using point3 = vec3;   // this tells us points as in a vector form

class ray{
    private:
      point3 orig;   // the original point, from where the ray emreges
      vec3 dir;   // the direction of the ray
    public :
    ray () {} // default constructor

    ray(const point3& origin, const vec3& direction) : orig(origin) , dir(direction) {} // comstructor
    const point3& origin() const  { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t){
        return orig + t*dir;  //new point, on the same line as of original and direction
    }

};