#include <iostream>
#include <vector>
#include <algorithm>

//Custom Headerfiles
#include "Headerfiles\general.hpp"
#include "Headerfiles\io.hpp"

using namespace std;

int main(){

    m m; // Class
    
    string baseDIR;
    cout << "Images dir -> ";
    cin >> baseDIR;
    cout << endl;

    int folders;
    cout << "number of subdirs -> ";
    cin >> folders;
    cout << endl;

    int images;
    cout << "Number of images in subdirs -> ";
    cin >> images;
    cout << endl;

    // IO data
    vector<vector<vector<double>>> data; // {{pixelvalues: {0, 255, 0, 255}, pixelvalues, pixelvalues, expected}, {pixelvalues, pixelvalues, pixelvalues, expected}} expected will always be last in group
    for(int i = 0; i < folders; i++){ // For each folder in dir
        vector<vector<double>> temp;

        for(int j = 0; j < images; j++){ // For each images in subdir
            temp.push_back(splitdata(read(baseDIR + "\\" + to_string(i) + "\\pixelvalues\\" + to_string(j) + ".txt"), ","));
        }
        temp.push_back(splitdata(read(baseDIR + "\\" + to_string(i) + "\\expected.txt"), ","));
        data.push_back(temp);
    }
    cout << "Pixelvalues and expected outputs loaded!" << endl;

    // Generation and Mutation parameters
    m.minimum = 0;
    m.maximum = 2;
    m.threshold = 3; // 0-10

    int generations;
    cout << "How many generations -> ";
    cin >> generations;
    cout << endl;

    int modelsPerGenerations;
    cout << "How many models per generation -> ";
    cin >> modelsPerGenerations;
    cout << endl;

    // Models
    // Log most accurate model to 'model.txt'. When the training ends, the most accurate model will be logged in 'model.txt'

    int best = 0; // Index of the best model. First model to get it going without special cases
    vector<vector<vector<vector<double>>>> models;
    models.push_back(m.modelTemplate(data[0][0].size(), 3, 15, 10)); // 1500 inputs, 3 hidden layers with 15 dimensions, output layer with 10 dimension
    m.weigh(models[0]);

    for(int gens = 0; gens < generations; gens++){

        vector<vector<vector<double>>> tmpModel = models[best]; // Copy best model to carry over to new array
        vector<vector<vector<vector<double>>>> models; // Clear array
        vector<double> correctness;
        models.push_back(tmpModel); // Put best model in 0th index

        // Populate generation
        for(int mods = 1; mods != modelsPerGenerations; mods++){ // 1-models per generations
            models.push_back(models[0]); // Duplicate most accurate model
            m.mutate(models[mods]); // Mutate model
        }

        // Propagate model
        
        for(int i = 0; i < models.size(); i++){
            double accumnear = 0;
            for(int groups = 0; groups < data.size(); groups++){
                for(int subgroups = 0; subgroups < data[groups].size() - 1; subgroups++){
                    m.inputs(models[i], data[groups][subgroups]);
                    m.propagte(models[i]);

                    accumnear += m.near(models[i], data[groups].back());
                }
            }
            correctness.push_back(accumnear); // Correctness of each model
        }

        auto maximum = minmax_element(correctness.begin(), correctness.end());

        best = *maximum.first;
        m.logmodel(models[best], "bestModel.txt");
    
    }

    //vector<vector<vector<double>>> genModel = m.modelTemplate();

    //m m; // LOL
//
    //m.maximum = 2;
    //m.minimum = 0;
//
    //m.threshold = 5;
//
    //vector<double> data = splitdata(read("images\\pixelvalues\\0.txt"), ",");
    //vector<vector<vector<double>>> model1 = m.modelTemplate(data.size(), 2, 3, 2);
    //vector<vector<vector<double>>> model2; // Copy the template to see if mutation is working
//
    //m.weigh(model1);
    //model2 = model1;
    //m.inputs(model1, data);
//
    //m.mutate(model2);
    //m.inputs(model2, data);
//
    //m.propagte(model1);
    //m.propagte(model2);
//
//
    //m.logmodel(model1, "model1.txt");
    //m.logmodel(model2, "model2.txt");
    
    //printmodel(model1);
    //printmodel(model2);
    //Modifies Vector hidden
    
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