#include <vector>
#include <sstream>
#include <iostream>

void printmodel(std::vector<std::vector<std::vector<double>>> data){
    for(int layer = 0; layer < data.size(); layer++){
        std::vector<std::vector<double>> layerdata = data[layer];
        for(int node = 0; node < layerdata.size(); node++){
            std::vector<double> nodedata = layerdata[node];
            std::cout << nodedata[0] << " | ";
            for(int weights = 1; weights < nodedata.size(); weights++){
                std::cout << nodedata[weights] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n" << std::endl;
    }
}

std::vector<double> splitdata(std::string file, std::string delim){ //Finish tomorrow
    size_t pos = 0;
    std::vector<double> out;

    std::string token;
    while ((pos = file.find(delim)) != std::string::npos) {
        token = file.substr(0, pos);
        out.push_back(std::stod(token));
        file.erase(0, pos + delim.length());
    }

    return out;
}

void printvec(std::vector<double> data){
    for(int i = 0; i < data.size(); i++){
        std::cout << data[i] << ", ";
    }
}

class m { // Model

private:
    double rnd(double randomMIN, double randomMAX){
        double f = (double)rand()/RAND_MAX;
        return randomMIN + f * (randomMAX - randomMIN);
    }

public:
    std::vector<std::vector<std::vector<double>>> modelTemplate(int inputdimension, int hiddenLayer, int hiddenLayerDimensions, int finalLayerDimension){
        using namespace std; // So that I don't have to "std::" everwhere in functions - It is declared in the local scope and therefore will not disturb main.cpp
        
        vector<vector<vector<double>>> out; // Set length of Vector
        
        ////     First layer    ////
        out.push_back(
            vector<vector<double>> (
                inputdimension + 1, // Layer length +1 for constant

                vector<double>( // Default value
                    hiddenLayerDimensions + 1, // Node length
                    1 // Default value
                )
            )
        );
        
        ////    Hidden layers   ////
        for(int i = 1; i < hiddenLayer; i++){
            out.push_back(
                vector<vector<double>> (
                    hiddenLayerDimensions, // Layer length

                    vector<double> ( // Default Value
                        hiddenLayerDimensions + 1, // Node Length
                        1 // Default value
                    )
                )
            );
        }

        //// Final hidden layer ////
        out.push_back(
            vector<vector<double>> (
                hiddenLayerDimensions, // Hidden layer length

                vector<double> ( // Default Value
                    finalLayerDimension + 1, // Node length
                    1 // Default value 
                )
            )
        );
        
        ////    Output layer    ////
        out.push_back(
            vector<vector<double>> (
                finalLayerDimension,

                vector<double> (
                    1,
                    1
                )
            )
        );

        return out;
    }
    
    void weigh(std::vector<std::vector<std::vector<double>>> &model, double min, double max){ // Pass vector refrence // Add weights
        using namespace std;

        // model.at(i) = [data] | model[i] = [data]

        for(int top = 0; top < model.size() - 1; top++){
            for(int nodes = 0; nodes < model[top].size(); nodes++){
                for(int weights = 1; weights < model[top][nodes].size(); weights++){
                    model.at(top).at(nodes).at(weights) = rnd(min, max);
        }}} // End of 'for' loops
    }

    void inputs(std::vector<std::vector<std::vector<double>>> &model, std::vector<double> inputs){
        using namespace std;

        for(int nodes = 1; nodes < model[0].size(); nodes++){
            model.at(0).at(nodes).at(0) = inputs[nodes - 1];
        }
    }
};
// End of Class