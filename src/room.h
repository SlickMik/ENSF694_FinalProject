#pragma once

#include <string>

struct Booking {
    std::string room;
    std::string title;
    int day = 0;
    int startHour = 0;
    int endHour = 0;
};

const int MAX_ROOM_BOOKINGS = 100;

// Each room also keeps its own list of bookings
struct Room {
    std::string roomId;
    int capacity = 0;
    std::string roomType;
    Booking bookings[MAX_ROOM_BOOKINGS];
    int bookingCount = 0;

    bool addBooking(const Booking& booking);
    bool removeBooking(int day, int hour);
};
