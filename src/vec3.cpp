#include "vec3.hpp"
#include <cmath>
#include <iostream>

class vec3{
    public :
        double e[3];
        vec3() : e{0,0,0} {}   // initializing default constructor
        vec3(double x, double y, double z) : e{x,y,z} {}  // initializing constructor

        double x() const {return e[0];}  // functions to call elements of vectors (not changeable)
        double y() const {return e[1];}
        double z() const {return e[2];}

        double mod() const {
            double t = x()*x() + y()*y() + z()*z();
            t = sqrt(t);
            return t;
        }
        double mod_squared() const{
            return x()*x() + y()*y() + z()*z();
        }
        vec3 operator-() const {    // we are using const here to make a copy of that vector
            return vec3(-x(),-y(),-z());
        }
};
vec3 operator+(const vec3& u, const vec3& v){   // here we called const as well as passsed vec3 by reference "&", which says that it wont copy(thus saving us space as we wont be making two another vectors "here u and v" as well time "copying takes time")
    return vec3(u.x()+v.x(),u.y()+v.y(),u.z()+v.z());  //and const helps us says that we wont mutate the orignal vector
}
vec3 operator-(const vec3& u, const vec3& v){
    return vec3(u.x()-v.x(),u.y()-v.y(),u.z()-v.z());
}
vec3 operator*(double t,const vec3& u){
    return vec3(u.x()*t,u.y()*t,u.z()*t);
}
vec3 operator/(const vec3& u, double t){
    return vec3(u.x()/t,u.y()/t,u.z()/t);
}
double dot(const vec3& v, const vec3& u){
    return (v.x()*u.x()) + (v.y()*u.y()) + (v.z()*u.z());
}
vec3 cross(const vec3& v,const vec3& u){
   return vec3((v.y()*u.z())-(v.z()*u.y()),(v.z()*u.x())-(v.x()*u.z()),(v.x()*u.y())-(v.y()*u.x()));
}
vec3 operator+=(vec3 &v,const vec3 &u){
    v = v + u;
    return v;
}