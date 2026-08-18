#include "campus.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

int Campus::find(const std::string& name) const {
    for (int i = 0; i < buildingCount; ++i)
        if (buildings[i].name == name) return i;
    return -1;
}


//Adds building to campus from file
int Campus::add(const std::string& name) {
    int index = find(name);

    if (index >= 0) return index;

    if (buildingCount == MAX_BUILDINGS) throw std::overflow_error("Campus is full");

    buildings[buildingCount].name = name;

    return buildingCount++;

}


// Loads buildings from local file
void Campus::load(const std::string& file_name) {
    std::ifstream input(file_name);
    if (!input) throw std::runtime_error("File isn't found");
    std::string line;
    while (std::getline(input, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::stringstream row(line); 
        
        std::string first, second, weight;
        std::getline(row, first, ','); 

        std::getline(row, second, ',');

        std::getline(row, weight);

        int a = add(first), b = add(second);

        if (!weights[a][b]) ++edgeCount;

        weights[a][b] = weights[b][a] = std::stoi(weight);
    }
}

int Campus::weight(int first, int second) const { return weights[first][second];}

const Building& Campus::building(int index) const { return buildings[index]; }

int Campus::building_count() const { return buildingCount;}

int Campus::edge_count() const { return edgeCount; }
