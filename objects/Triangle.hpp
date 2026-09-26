#pragma once

#include "Math/constants.hpp"
#include "../raytracer/hittable.hpp"
#include <cmath>


inline bool same_side(double d1, double d2) {
    return (d1 * d2) >= 0;
}

class triangle : public hittable{
    private :
        point3 p1;
        point3 p2;
        point3 p3;
        vec3 n;
        
    
    public :
        triangle(const point3& p1, const point3& p2, const point3& p3) : p1(p1), p2(p2), p3(p3) { //constructor
            n = cross((p1-p2),(p3-p1));
        }

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record &h) const override{

            auto b = r.direction();
            auto a = r.origin();
            auto denominator = dot(b,n);
            auto numerator = dot(p1,n) - dot(a,n);
            if(std::fabs(denominator) < 1e-8){  // if b is perpendicular to normal of the plane
                return false;
            }
            auto t = (double)numerator/denominator; // it computes t from plane equation (P)dot(n) = (p1)dot(n)

            if(t <= ray_tmin || t >= ray_tmax){
                return false;
            }
            auto p = r.at(t);
            auto c1 = cross((p2-p1),(p-p1));
            auto c2 = cross((p3-p2),(p-p2));
            auto c3 = cross((p1-p3),(p-p3));
            if (same_side(dot(c1,n), dot(c2,n)) && same_side(dot(c2,n), dot(c3,n))) {
                h.p = p;
                h.t = t;
                h.normal = unit(n);
                return true;    
            } 

            return false; // critical fix: must return false if point is outside the triangle
        }
};