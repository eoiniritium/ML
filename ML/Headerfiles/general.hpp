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


//Generate model