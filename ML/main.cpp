#include <iostream>
#include <vector>

//Custom Headerfiles
#include "Headerfiles\general.hpp"
#include "Headerfiles\io.hpp"

using namespace std;


int main(){
    m m; // LOL

    //Modifies Vector hidden
    vector<double> data = splitdata(read("images\\pixelvalues\\0.txt"), ",");

    // Model
    vector<vector<vector<double>>> model = m.modelTemplate(data.size(), 2, 3, 2);
    m.weigh(model, 0.2, 0.6); // Add weights to model

    // Calculations
    vector<vector<vector<double>>> ran = model;
    m.inputs(ran, data); // Add the inputs in
    //m.propagte(ran); // Feed the data through

    printmodel(ran); // Print the new model
    

    return 0;
}