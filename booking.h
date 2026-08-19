#pragma once

#include "room.h"

const int MAX_BOOKINGS = 200;

class BookingSystem {
    Booking bookings[MAX_BOOKINGS];
    int bookingCount = 0;

   
public:
    bool isAvailable(const std::string& room, int day, int startHour, int endHour) const;
    bool add(const Booking& booking);
    bool remove(const std::string& room, int day, int hour);
    const Booking* get(const std::string& room, int day, int hour) const;
    int between(int day, int firstHour, int lastHour, Booking result[], int capacity) const;
    int onDay(int day, Booking result[], int capacity) const;
    const Booking* next(int day, int hour) const;
    int size() const;
};
