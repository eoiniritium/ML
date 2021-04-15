#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Custom Headerfiles
#include "Headerfiles\general.hpp"
#include "Headerfiles\io.hpp"


using namespace std;

int main(){

    m m; // Init class
    vector<vector<vector<double>>> images;
    images = m.load_images("images", 0, 9, 0, 1, ",");
    m.logmodel(images, "images.txt"); // Ghetto replacement

    vector<vector<double>> expected;
    expected = m.load_expected("images", 0, 9, ",");
    printexptected(expected);
    
    return 0;
}