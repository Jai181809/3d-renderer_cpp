#pragma once
#include <iostream>

#include "hittable.hpp"
#include <memory>
#include <vector>


using namespace std;

class hittable_list : public hittable{
    public:
        vector<shared_ptr<hittable>> objects;   //object is a shared ptr# (write abt shared_ptr)

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear(){ objects.clear();}
        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
    }

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record &h) const override {   // understand this shi and write it down ###
        hit_record temp;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;
        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp)) {  
                hit_anything = true;
                closest_so_far = temp.t;
                h = temp;
            }
        }

        return hit_anything;

    }


};