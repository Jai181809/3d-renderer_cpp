#pragma once
#include "Math/constants.hpp"

using namespace std;

class interval{
    public:

        double min;
        double max;
        interval() : min(infinity), max(-infinity) {}  // default interval is empty
        interval(double min, double max) : min(min), max(max) {}

        double size()const{
            return max - min;
        }

        bool contains(double x){
            return min <= x && x<= max;
        }

        bool surrounds(double x) const{
            return min < x && x < max;
        }

        double clamp(double x) const{
            if(x<min) {return min;}
            if(x > max) {return max;}
            return x;
        }

        static const interval empty, universe;

};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
