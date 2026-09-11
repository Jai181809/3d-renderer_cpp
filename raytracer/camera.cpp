#include <iostream>
#include "math/vec3.hpp"
#include "ray.hpp"

using namespace std;


class camera{
    public: 
      double aspect_ratio = 16.0 / 9.0;
      int Im_width = 400;  // Calculate the image height, and ensure that it's at least 1.
      vec3 camera_center = point3(0,0,0); // Camera position
      double focal_length = 1.0;

      void initialize(){
        int Im_height = int(Im_width / aspect_ratio);
        Im_height = (Im_height < 1) ? 1 : Im_height;

         // Viewport widths less than one are ok since they are real valued.
        viewport_height = 2.0;
        viewport_width = viewport_height * (double(Im_width)/Im_height);
        auto viewport_u = vec3(viewport_height,0,0); // we call it in function defination itself as it would be scrapped after the function is done
        auto viewport_v = vec3(0,-viewport_height,0);   //here it is going down as ppm is defined as that way, and we need to go down in our camera(real world)
        auto delta_u = viewport_u/Im_width;
        auto delta_v = viewport_v/Im_height;
        auto 
      }
      
      


    private:
      int Im_height;
      double viewport_height;
      double viewport_width;
};