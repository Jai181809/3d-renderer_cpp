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


};
vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.x()+v.x(),u.y()+v.y(),u.z()+v.z());
}
vec3 operator-(const vec3& u, const vec3& v){
    return vec3(u.x()-v.x(),u.y()-v.y(),u.z()-v.z());
}
vec3 operator*(double,const vec3& u){
    return vec3(u.x()*t,u.y()*t,u.z()*t);
}
vec3 operator/(const vec3& u, double t){
    return vec3(u.x()/t,u.y()/t,u.z()/t);
}