#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class vec3{
    public :
        double e[3];
        vec3() : e{0,0,0} {}   // initializing default constructor
        vec3(double x, double y, double z) : e{x,y,z} {}  // initializing constructor

        double x() const ;  // functions to call elements of vectors (not changeable)
        double y() const ;
        double z() const;

        double mod() const;
        double mod_squared() const;
        vec3 operator-() const;
};

vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(double t,const vec3& u);
vec3 operator/(const vec3& u, double t);
double dot(const vec3& v, const vec3& u);
vec3 cross(const vec3& v,const vec3& u);
vec3 operator+=(vec3 &v,const vec3 &u);