#pragma once

#include "ray.hpp"
#include <iostream>

using namespace std;

class hit_record{   //stores data important during ray hitting object
    public: 
      point3 p; // point of intersection of the object
      vec3 normal;  //normal at that point
      double t;   //distance of that point from center
};

class hittable{
    public:
        virtual ~hittable() = default;  // destroys the data after the object is deleted, '~' is a destructor !!!
        
        virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record &h) const = 0;  // here '= 0' says that the function has no specific body and changes for easch inheritence of class(in sphere a hit function would be different than for a triangle)
};