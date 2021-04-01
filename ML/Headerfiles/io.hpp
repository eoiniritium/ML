#include <fstream>

std::string read(std::string file){
    std::ifstream f(file);
    std::string output;
    
    f >> output;
    return output;
}

void output(std::string file, std::string data){
    std::ofstream f(file);

    f << data;
}