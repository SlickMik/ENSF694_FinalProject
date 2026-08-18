#pragma once

#include "room.h"

struct Location { double x = 0, y = 0; };

class Building {
public:
    std::string id, name;
    Location location;
    HashTable<Room, 11> rooms;

    Building() = default;
    Building(const std::string& id, const std::string& name, Location location);
};
