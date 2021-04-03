#include <iostream>
#include <vector>

//Custom Headerfiles
#include "Headerfiles\general.hpp"
#include "Headerfiles\io.hpp"

using namespace std;


int main(){
    m m; // LOL

    vector<vector<vector<double>>> model = m.modelTemplate(3, 5, 3, 2);

    printmodel(model);
}