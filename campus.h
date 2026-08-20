#pragma once

#include "building.h"

const int MAX_BUILDINGS = 20;

class Campus {
    Building buildings[MAX_BUILDINGS];
    int weights[MAX_BUILDINGS][MAX_BUILDINGS]{};
    int buildingCount = 0;
    int edgeCount = 0;

    int add(const std::string& name);
public:
    void load(const std::string& file_name);
    int find(const std::string& name) const;
    int weight(int first, int second) const;
    const Building& building(int index) const;
    bool addRoom(const std::string& buildingId, const Room& room);
    Room* findRoom(const std::string& roomId);
    const Room* findRoom(const std::string& roomId) const;
    Room& room(int index);
    const Room& room(int index) const;
    int room_count() const;
    int building_count() const;
    int edge_count() const;
};
