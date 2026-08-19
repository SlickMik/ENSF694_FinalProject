#pragma once

#include <string>

struct Room {
    std::string name;
};

struct Booking {
    std::string room;
    std::string title;
    int day = 0;
    int startHour = 0;
    int endHour = 0;
};
