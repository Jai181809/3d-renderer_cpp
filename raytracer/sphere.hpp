#pragma once

#include <iostream>
#include "math/vec3.hpp"
#include "raytracer/ray.hpp"
#include "hittable.hpp"


class sphere : public hittable {        // here sphere is inheriting the abstract hittable class, this tells the compiler that this is a hittable object

private:
    point3 center;
    double radius;
        
public:
    sphere(const point3& center, double radius) : center(center), radius(fmax(0,radius)) {} //constructor
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record &h) const override{     // here is the abstract function, only for sphere here
        // const overide meansconst wont change anything and overide says that it will overide the base function
        vec3 oc = center - r.origin();   //gets the vector between the origin(camera) and sphere center
        auto d = r.direction();   // gets the ray direction
        auto a = dot(d,d);
        auto b = -2*(dot(d,oc));
        auto c = dot(oc,oc) - radius*radius;
        auto disc = b*b - 4*a*c;    
        
        if(disc < 0){return false;}
        
        auto sqrtd = sqrt(disc);
        auto root = (-b-sqrtd)/(2*a);
    }                          
};


/*
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
*/

