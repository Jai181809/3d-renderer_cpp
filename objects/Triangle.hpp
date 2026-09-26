#pragma once

#include "Math/constants.hpp"
#include "../raytracer/hittable.hpp"

class triangle : public hittable{
    private :
        point3 p1;
        point3 p2;
        point3 p3;
        
    
    public :
        triangle(const point3& p1, const point3& p2, const point3& p3) : p1(p1), p2(p2), p3(p3) {} //constructor
        
        vec3 n = cross((p1-p2),(p3-p1));
        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record &h) const override{
            auto b = r.direction();
            auto a = r.origin();
            auto de = dot(b,n);
            auto df = dot(a,n);
            if(de == 0){
                return false;
            }
            auto t = (double)df/de;
            auto p = r.at(t);
            auto c1 = cross((p1-p2),(p-p2));
            auto c2 = cross((p2-p3),(p-p3));
            auto c3 = cross((p3-p1),(p-p1));
            if(dot(c1,n)/abs(dot(c1,n)) == dot(c2,n)/abs(dot(c2,n))){
                if(dot(c3,n)/abs(dot(c3,n)) == dot(c2,n)/abs(dot(c2,n))){
                    h.p = p;
                    h.t = t;
            }

            
        }





};