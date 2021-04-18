//Why so much?
#include <vector>
#include <sstream>
#include <iostream>
#include <numeric>
#include <math.h>
#include <fstream>

void printexptected(std::vector<std::vector<double>> &data){ // Pass by referance
    for(int i = 0; i < data.size(); i++){

        for(int j = 0; j < data[i].size(); j++){ // Can't go over because integer overflow
            std::cout << data[i][j] << ' ';
        }

        std::cout << std::endl;
    }
}

void printmodel(std::vector<std::vector<std::vector<double>>> &data){ // Referance because faster
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

std::vector<double> splitdata(std::string data, char delim){ ////////////
    using namespace std;
    vector<double> out;
    
    string temp = "";
    for(int i = 0; i < data.length(); i++){
        
        if(data[i] != delim){
            temp += data[i];
        } else {
            out.push_back(stod(temp));
            temp = "";
        }
    }
    return out;
}

void printvec(std::vector<double> &data){ // Referance for faster speed because it is around 16 Bits and the vector is greater
    for(int i = 0; i < data.size(); i++){
        std::cout << data[i] << ", ";
    }
}

void printlayer(std::vector<std::vector<double>> &data){
    for(int node = 0; node < data.size(); node++){
        for(int weight = 0; weight < data[node].size(); weight++){
            std::cout << data[weight][node] << ", ";
        }
        std::cout << std::endl;
    }
}

void printdim(std::vector<std::vector<std::vector<double>>> input){
    using namespace std;

    
}


// Model
class m {
private:
    double rnd(double randomMIN, double randomMAX){
        double f = (double)rand()/RAND_MAX;
        return randomMIN + f * (randomMAX - randomMIN);
    }

    double sigmoid(double x){
        return x / (1 + abs(x));
    }

    double activation(std::vector<double> inValues){
        double sum = 0;

        for(int i = 0; i  < inValues.size(); i++){
            sum += inValues[i];
        }

        return sigmoid(sum);
    }

    std::string read(std::string file){
        std::ifstream f(file);
        std::string output;
        
        f >> output;
        return output;
    }

    void write(std::string file, std::string data){
        std::ofstream f(file);

        f << data;
    }

public:

    double minimum;
    double maximum;
    double threshold;

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
    
    void weigh(std::vector<std::vector<std::vector<double>>> &model){ // Pass vector refrence // Add weights
        using namespace std;

        // model.at(i) = [data] | model[i] = [data]

        for(int top = 0; top < model.size() - 1; top++){
            for(int nodes = 0; nodes < model[top].size(); nodes++){
                for(int weights = 1; weights < model[top][nodes].size(); weights++){
                    model.at(top).at(nodes).at(weights) = rnd(minimum, maximum);
        }}} // End of 'for' loops
    }

    void inputs(std::vector<std::vector<std::vector<double>>> &model, std::vector<double> inputs){
        using namespace std;

        for(int nodes = 1; nodes < model[0].size(); nodes++){
            model.at(0).at(nodes).at(0) = inputs[nodes - 1];
        }
    }

    // Modify Model to be correct
    void propagte(std::vector<std::vector<std::vector<double>>> &model){
        using namespace std;
        // Model[0][0][0] = [which layer] [which node] [node value/connection]
        for(int layer = 1; layer < model.size(); layer++){ // For each layer in the model
            for(int node = 0; node < model[layer].size(); node++){ // For each node in the previous layer
                
                // Connection values
                vector<double> incomingvalues;
                for(int prevnodes = 0; prevnodes < model[layer - 1].size(); prevnodes++){ // Size of the prev layer
                    incomingvalues.push_back(model[layer - 1][prevnodes][node + 1] * model[layer-1][prevnodes][0]); // Prev layer, node in prev layer, current node (+1 because of the first index being value)
                }

                //Node Value
                model.at(layer).at(node).at(0) = activation(incomingvalues);
            }
        }
    }

    void mutate(std::vector<std::vector<std::vector<double>>> &model){
        using namespace std;

        for(int layers = 0; layers + 1 < model.size(); layers++){ // Each layer in the model but the last one

            for(int nodes = 0; nodes < model[layers].size(); nodes++){ // Each node in the layer

                for(int weight = 1; weight < model[layers][nodes].size(); weight++){ // Each weight in the node

                    double mutateQ;

                    mutateQ = rnd(0, 10);

                    if(mutateQ > threshold){
                        double newW = rnd(minimum, maximum);

                        model.at(layers).at(nodes).at(weight) = newW;
                    }
                }
            }
        }
    }

    double near(std::vector<std::vector<std::vector<double>>> &model, std::vector<double> expected){
        // Smallest is bests because less diff, sum
        using namespace std;
        
        double out = 0;
        for(int last = 0; model.back().size(); last++) {
            out += pow(expected[last], 2) - pow(model[model.size()-1][last][0], 2);
        }

        return out;
    }

    void logmodel(std::vector<std::vector<std::vector<double>>> &model, std::string file){
        using namespace std;

        ofstream f(file); // File writter at location


        string concat;
        for(int layer = 0; layer < model.size(); layer++){

            for(int node = 0; node < model[layer].size(); node++){
                
                concat += to_string(model[layer][node][0]) + "| ";
                for(int weight = 1; weight < model[layer][node].size(); weight++){
                    concat += to_string(model[layer][node][weight]);

                    if(!(weight == model[layer][node].size() -2)){
                        concat += ", ";
                    }
                }

                concat += "\n";
            }

            concat += "\n\n";
        }

        f << concat;
    }

    std::vector<std::vector<std::vector<double>>> load_images(std::string base_dir, int folderBottom, int folderTop, int imageBottom, int imageTop, char delim){ // Can use logmodel on this but it might be strange
        using namespace std;

        vector<vector<vector<double>>> data;
        
        for(int folder = folderBottom; folder <= folderTop; folder++){
            vector<vector<double>> group_data;

            for(int image = imageBottom; image <= imageBottom; image++){
                string dir;
                dir = base_dir + "\\" + to_string(folder) + "\\pixelvalues\\" + to_string(image) + ".txt"; //Read data from here
                
                string image_temp;
                image_temp = read(dir);

                group_data.push_back(splitdata(image_temp, delim));
            }

            data.push_back(group_data);
        }

        return data;
    } // Working

    std::vector<std::vector<double>> load_expected(std::string base_dir, int folderBottom, int folderTop, char delim){
        using namespace std;

        vector<vector<double>> data;

        for(int i = folderBottom; i <= folderTop; i++){
            string dir;
            dir = base_dir + "\\" + to_string(i) + "\\expected.txt";
            string tempdata = read(dir);

            cout << tempdata << endl; //Debugging
            vector<double> temp;
            temp = splitdata(tempdata, delim);
            data.push_back(temp);
        }

        return data;
    }
};