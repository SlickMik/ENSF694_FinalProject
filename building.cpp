#include "building.h"

Building::Building(const std::string& id, const std::string& name, Location location)
    : buildingId(id), name(name), location(location) {}

bool Building::addRoom(const Room& room) {
    // Do not add the same room twice
    if (roomCount == MAX_ROOMS_PER_BUILDING || findRoom(room.roomId)) return false;
    rooms[roomCount++] = room;
    return true;
}

Room* Building::findRoom(const std::string& roomId) {
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].roomId == roomId) return &rooms[i];
    return nullptr;
}

const Room* Building::findRoom(const std::string& roomId) const {
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].roomId == roomId) return &rooms[i];
    return nullptr;
}
