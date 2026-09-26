#pragma once

#include "Math/constants.hpp"
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
        if (root <= ray_tmin || root >= ray_tmax){
            root = (-b+sqrtd)/(2*a);
            if (root <= ray_tmin || ray_tmax <= root){
                return false;
            }
        }
        
        h.t = root;
        h.p = r.at(h.t);  // getting point from center to (the ray r is originating from camera, and has a direction defined)
        vec3 outward_normal = (h.p - center)/radius ;  //normal
        h.set_face_normal(r,outward_normal);  // calling the function to decide the normal in h variable class (defined)
        return true;
    }
};



