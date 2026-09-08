#include "Image_opener.hpp"  // header file
#include <cstdlib>
#include <iostream>

using namespace std;

void Convertimage(string inPath,string outPath){
    string command = "magick " + inPath + " " + outPath;
    system(command.c_str());     // this converts to strings in c
    return;
}
void Openimage(string outPath){
    string command = "start "+ outPath;
    system(command.c_str());
    return;

}




