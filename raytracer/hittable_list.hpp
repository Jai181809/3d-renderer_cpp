#pragma once
#include <iostream>

#include "hittable.hpp"
#include <vector>
#include "Math/constants.hpp"




class hittable_list : public hittable{
    public:
        vector<shared_ptr<hittable>> objects;   //object is a shared ptr

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
            if (object->hit(r, ray_tmin, closest_so_far, temp)) {    // here it calls the objects function(say the object was the triangle class[hittable class] so it will be called then the hit function will be called for it)
                hit_anything = true;
                closest_so_far = temp.t;  
                h = temp;  // here h starts recording those object(only one object) that hits and returns true
            }
        }

        return hit_anything;

    }
};

/*

how it works:
    say first tmax was 100
    then the loop starts and the first object had t = 5,
        this becomes the new tmax for hit function
    then the next object comes, if it doesnt hit for the range between tmin and 5, then next object comes,,
        this happens for all objects (say t were[5,6,2,4])
            now the third will come and will return a true val, tmax become 2 
        now even if the fuinal object comes, the t wont be satisfying the range hence will return false
    in the end, hit_record h holds only that value that has the lowest t
this function then returns a bool value
*/