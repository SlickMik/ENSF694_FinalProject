#pragma once

#include "room.h"
#include <string>

struct Location {
    double x = 0;
    double y = 0;
};

const int MAX_ROOMS_PER_BUILDING = 3;

struct Building {
    std::string buildingId;
    std::string name;
    Location location;
    Room rooms[MAX_ROOMS_PER_BUILDING];
    int roomCount = 0;

    Building() = default;
    Building(const std::string& buildingId, const std::string& name, Location location);
    bool addRoom(const Room& room);
    Room* findRoom(const std::string& roomId);
    const Room* findRoom(const std::string& roomId) const;
};
