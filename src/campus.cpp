#include "campus.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

int Campus::find(const std::string& name) const {
    for (int i = 0; i < buildingCount; ++i)
        if (buildings[i].name == name) return i;
    return -1;
}


// Adds a building only if it is new
int Campus::add(const std::string& name) {
    int index = find(name);

    if (index >= 0) return index;

    if (buildingCount == MAX_BUILDINGS) throw std::overflow_error("Campus is full");

    buildings[buildingCount] = Building(name, name, {});

    return buildingCount++;

}


// Loads one connection from each line in the file
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

        // An undirected edge is only counted once
        if (!weights[a][b]) ++edgeCount;

        weights[a][b] = weights[b][a] = std::stoi(weight);
    }
}

int Campus::weight(int first, int second) const { return weights[first][second];}

const Building& Campus::building(int index) const { return buildings[index]; }

bool Campus::addRoom(const std::string& buildingId, const Room& room) {
    int index = find(buildingId);
    return index >= 0 && buildings[index].addRoom(room);
}

Room* Campus::findRoom(const std::string& roomId) {
    for (int i = 0; i < buildingCount; i++) {
        Room* room = buildings[i].findRoom(roomId);
        if (room) return room;
    }
    return nullptr;
}

const Room* Campus::findRoom(const std::string& roomId) const {
    for (int i = 0; i < buildingCount; i++) {
        const Room* room = buildings[i].findRoom(roomId);
        if (room) return room;
    }
    return nullptr;
}

Room& Campus::room(int index) {
    for (int i = 0; i < buildingCount; i++) {
        if (index < buildings[i].roomCount) return buildings[i].rooms[index];
        index -= buildings[i].roomCount;
    }
    throw std::out_of_range("room not found");
}

const Room& Campus::room(int index) const {
    for (int i = 0; i < buildingCount; i++) {
        if (index < buildings[i].roomCount) return buildings[i].rooms[index];
        index -= buildings[i].roomCount;
    }
    throw std::out_of_range("room not found");
}

int Campus::room_count() const {
    int count = 0;
    for (int i = 0; i < buildingCount; i++) count += buildings[i].roomCount;
    return count;
}

int Campus::building_count() const { return buildingCount;}

int Campus::edge_count() const { return edgeCount; }
