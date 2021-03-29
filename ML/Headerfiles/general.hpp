#include <vector>
#include <sstream>

#include "io.hpp" //BAD! Must refactor but no❤️

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
    std::string data = read(file);
    std::stringstream ss(data);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
}