#include <iostream>
#include <fstream>
#include "src/Image_opener.hpp"
#include "math/vec3.hpp"
#include "src/colour.hpp"
using namespace std;

int main() {
    ofstream File("Image.ppm");     // writing on a file so that i can save the ppm output


    // Image dimension
    int Im_length = 256;
    int Im_width = 256;
    File << "P3\n" << Im_length << ' ' << Im_width << "\n255\n";   // writung on the ppm file(image.ppm)

    for (int j = 0; j < Im_length; j++) {
        clog << "\rScanlines remaining: " << (Im_length - j) << ' ' << std::flush;
        for (int i = 0; i < Im_width; i++) {
            auto pixel_colour = colour(double(i)/(Im_width-1),double(j)/(Im_length-1),0);
            colour wr = write_color(cout,pixel_colour);
            File << wr.x() << " " << wr.y() << " " << wr.z() << "\n";

        }
        
    }
    clog << "\rDone.                 \n";
    File.close();
    Convertimage("image.ppm","image.png");
    Openimage("image.png");

    return 0;
}