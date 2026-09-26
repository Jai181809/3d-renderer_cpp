#include <iostream>
#include <fstream>
#include "src/Image_opener.hpp"
#include "raytracer/camera.hpp"
using namespace std;

int main() {
        // writing on a file so that i can save the ppm output
    camera cl;
    cl.render("image.ppm");


    Convertimage("image.ppm","image.png");
    Openimage("image.png");

    return 0;
}