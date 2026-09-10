#pragma once

#include <iostream>

class vec3 {
public:
    double e[3];

    vec3();
    vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    double mod() const;
    double mod_squared() const;

    vec3 operator-() const;
    
};

// Non-member operator declarations
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& u);
vec3 operator/(const vec3& u, double t);
vec3 unit(const vec3 &v) ;

double dot(const vec3& v, const vec3& u);
vec3 cross(const vec3& v, const vec3& u);

vec3& operator+=(vec3& v, const vec3& u);