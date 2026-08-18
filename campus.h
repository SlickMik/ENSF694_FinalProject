#pragma once

#include "building.h"

const int MAX_BUILDINGS = 32;

class Campus {
    Building buildings_[MAX_BUILDINGS];
    bool active_[MAX_BUILDINGS]{};
    int weights_[MAX_BUILDINGS][MAX_BUILDINGS]{};
    HashTable<int, 67> index_;
public:
    bool add(const Building& building);
    bool remove(const std::string& id);
    Building* find(const std::string& id);
    const Building* find(const std::string& id) const;
    void connect(const std::string& first, const std::string& second, int weight);
    int slot(const std::string& id) const;
    bool active(int slot) const;
    int weight(int first, int second) const;
    const Building& building(int slot) const;
    int building_count() const;
    int edge_count() const;
};
