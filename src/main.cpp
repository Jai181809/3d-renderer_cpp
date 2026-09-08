#include <iostream>
#include <fstream>
#include "Image_opener.hpp"
using namespace std;

int main() {
    ofstream File("Image.ppm");     // writing on a file so that i can save the ppm output


    // Image dimension
    int Im_length = 256;
    int Im_width = 256;
    File << "P3\n" << Im_length << ' ' << Im_width << "\n255\n";   // writung on the ppm file(image.ppm)

    for (int j = 0; j < Im_length; j++) {
        for (int i = 0; i < Im_width; i++) {
            auto b = double(i) / (Im_width-1);
            auto g = double(j) / (Im_length-1);
            auto r = 0.0;

            int ir = int(255.999 * r);  // we multipply with 255.999 so that we dont missout/ overflow to 256
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            File << ir << ' ' << ig << ' ' << ib << '\n';   // writung on the ppm file(image.ppm)
        }
        
    }
    File.close();
    Convertimage("image.ppm","image.png");
    Openimage("image.png");

    return 0;
}