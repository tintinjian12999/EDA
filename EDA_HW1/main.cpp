#include "main.h"
int main (int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "The number of Input files must be 1!" << std::endl;
        return 1;
    }
    std::string file_name = argv[1];
    std::ifstream file;

    file_name.append(".dfg");
    file.open(file_name);
    if (file.fail()) {
        std::cout << "Open failed" << std::endl;
        return 1;
    }
    int v = 0, L = 0;
    std::vector<std::vector<int>> data;
    read_line (data, file, v, L);
    return 0;
} 

void read_line(std::vector<std::vector<int>>& data, std::ifstream& file, int& v, int& L) 
{
    file >> v >> L;
    file.ignore(1, '\n'); // Ignore the '/n' in first line
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }
}