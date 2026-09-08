#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream File("Image.ppm");


    // Image dimension
    int Im_length = 256;
    int Im_width = 256;
    File << "P3\n" << Im_length << ' ' << Im_width << "\n255\n";

    for (int j = 0; j < Im_length; j++) {
        for (int i = 0; i < Im_width; i++) {
            auto r = double(i) / (Im_width-1);
            auto g = double(j) / (Im_length-1);
            auto b = 0.0;

            int ir = int(255.999 * r);  // we multipply with 255.999 so that we dont missout/ overflow to 256
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            File << ir << ' ' << ig << ' ' << ib << '\n';
        }
        
    }
    File.close();

    return 0;
}