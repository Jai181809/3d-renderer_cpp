#pragma once


#include <iostream>
#include "math/vec3.hpp"
#include "ray.hpp"
#include "src/colour.hpp"
#include <fstream>

using namespace std;


colour ray_color(const ray& r) {
    vec3 unit_direction = unit(r.direction());       // here this function defines the colour of the output, but it is subjected to change(will be added to colour.hpp later)
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*colour(1.0, 1.0, 1.0) + a*colour(0.5, 0.7, 1.0);
}

class camera{
    public: 
      double aspect_ratio = 16.0 / 9.0;
      int Im_width = 400;
      vec3 camera_center = point3(0,0,0); // Camera position
      double focal_length = 1.0;

      void initialize(){
        Im_height = int(Im_width / aspect_ratio);              // no "int" — assigns member
        Im_height = (Im_height < 1) ? 1 : Im_height;

        // Viewport widths less than one are ok since they are real valued.
        viewport_height = 2.0;
        viewport_width = viewport_height * (double(Im_width)/Im_height);
        auto viewport_u = vec3(viewport_width,0,0);            // fixed: was viewport_height
        auto viewport_v = vec3(0,-viewport_height,0);
        delta_u = viewport_u/Im_width;                          // no "auto" — assigns member
        delta_v = viewport_v/Im_height;                         // no "auto" — assigns member
        auto viewport_upperleft = camera_center - vec3(0,0,focal_length)-(viewport_v/2)-(viewport_u/2);
        pixel_0_0 = viewport_upperleft + (delta_u+delta_v)/2;   // no "auto" — assigns member
        
      }

      void render(string path){
        initialize();
        ofstream File(path);
        File << "P3\n" << Im_width << " " << Im_height << "\n255\n";
        for(int j = 0;j<Im_height;j++){
          clog << "\rScanlines remaining: " << (Im_height - j) << ' ' << flush;
          for (int i = 0; i < Im_width; i++) {
            auto pixel_center = pixel_0_0 + (i *delta_u) + (j *delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            colour pixel_colour = ray_color(r);   // fixed: was ray_colour
            colour wr = write_color(cout, pixel_colour);
            
            File << wr.x() << " " << wr.y() << " " << wr.z() << "\n";
        
          }
        }
        File.close();
        clog << "\rDone.                 \n";
      }

    private:
      int Im_height;
      double viewport_height;
      double viewport_width;
      vec3 pixel_0_0;
      vec3 delta_u;
      vec3 delta_v;
};