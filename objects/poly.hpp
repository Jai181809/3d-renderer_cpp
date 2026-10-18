#pragma once

#include "vector"
#include "algorithm"
#include "triangle.hpp"



vec3 centroid(const vector<point3> points){
    vec3 sum = vec3(0,0,0);
    int n = points.size();
    for (const auto &point : points){
        sum += point;
    }
    auto center = sum/n;
    return center;
}

vec3 normal(const vector<point3> &points){
    vec3 n = cross((points[0]-points[1]),points[1]-points[2]);
    if(n.mod() == 0){
        n = cross((points[0]-points[1]),points[2]-points[3]);
    }
    return n;
}


class polygon : public hittable{
    private:
        vector<point3> points;
        vector<pair<double,point3>> pair_;
    public :

    polygon (const vector<point3> &points) : points(points) {}
    vec3 Center = centroid(points);
    vec3 norm = unit(normal(points));
    int n = points.size();
    vec3 u = unit(Center - points[0]);
    vec3 v = cross(norm,u);
    double angle_of(const point3 &point){
        return atan2(dot(point - Center,v),dot(point - Center,u));
    }
    void autopairing(){
        for(const auto &point : points){
            auto d =  angle_of(point);
            pair_.emplace_back(d,point);
        }
        sort(pair_.begin(), pair_.end());
    }

    void sorted(){
        points.clear();
        for(int i = 0; i <n; i++ ){
            points.push_back(pair_[i].second);
        }
    }


};




