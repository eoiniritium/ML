#include <iostream>
#include <vector>

//Custom Headerfiles
#include "Headerfiles\general.hpp"
#include "Headerfiles\io.hpp"

using namespace std;

int main(){
    m m; // LOL

    m.maximum = 2;
    m.minimum = 0;

    m.threshold = 5;

    vector<vector<vector<double>>> model1 = m.modelTemplate(3, 2, 3, 2);
    vector<vector<vector<double>>> model2; // Copy the template to see if mutation is working

    m.weigh(model1);
    model2 = model1;

    printmodel(model1);

    m.mutate(model2);
    printmodel(model2);


    //Modifies Vector hidden
    //vector<double> data = splitdata(read("images\\pixelvalues\\0.txt"), ",");
    //// Model
    //vector<vector<vector<double>>> model = m.modelTemplate(data.size(), 2, 3, 2);
    //m.minimum = 0.2;
    //m.maximum = 0.6;
    //m.weigh(model); // Add weights to mode
    //// Calculations
    //vector<vector<vector<double>>> ran = model;
    //m.inputs(ran, data); // Add the inputs in
    //m.propagte(ran); // Feed the data through
    ////printmodel(ran); // Print the new mode
//
    //m.mutate(model);
    //m.inputs(model, data);
    //m.propagte(model);

    //printmodel(model);

    return 0;
}