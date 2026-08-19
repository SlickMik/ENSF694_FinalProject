#include "booking.h"

// Finds where a date and time belongs in the sorted array.
int BookingSystem::lowerBound(int day, int hour) const {
    int wantedTime = day * 24 + hour;
    int left = 0;
    int right = bookingCount;

    while (left < right) {
        int middle = (left + right) / 2;
        int middleTime = bookings[middle].day * 24 + bookings[middle].startHour;

        if (middleTime < wantedTime) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

const Booking* BookingSystem::get(const std::string& room, int day, int hour) const {
    int position = lowerBound(day, hour);

    while (position < bookingCount) {
        const Booking& current = bookings[position];

        if (current.day != day || current.startHour != hour) {
            break;
        }

        if (current.room == room) {
            return &bookings[position];
        }

        position++;
    }

    return nullptr;
}

bool BookingSystem::isAvailable(const std::string& room, int day,
                                int startHour, int endHour) const {
    for (int i = 0; i < bookingCount; i++) {
        bool sameRoom = bookings[i].room == room;
        bool sameDay = bookings[i].day == day;
        bool overlaps = startHour < bookings[i].endHour && endHour > bookings[i].startHour;

        if (sameRoom && sameDay && overlaps) {
            return false;
        }
    }

    return true;
}

bool BookingSystem::add(const Booking& booking) {
    if (bookingCount == MAX_BOOKINGS) {
        return false;
    }

    if (booking.day < 0 || booking.startHour < 0 || booking.endHour > 24 ||
        booking.startHour >= booking.endHour) {
        return false;
    }

    if (!isAvailable(booking.room, booking.day, booking.startHour, booking.endHour)) {
        return false;
    }

    int position = lowerBound(booking.day, booking.startHour);

    for (int i = bookingCount; i > position; i--) {
        bookings[i] = bookings[i - 1];
    }

    bookings[position] = booking;
    bookingCount++;
    return true;
}

bool BookingSystem::remove(const std::string& room, int day, int hour) {
    int position = lowerBound(day, hour);

    while (position < bookingCount) {
        if (bookings[position].day != day || bookings[position].startHour != hour) {
            return false;
        }

        if (bookings[position].room == room) {
            break;
        }

        position++;
    }

    if (position == bookingCount) {
        return false;
    }

    for (int i = position; i < bookingCount - 1; i++) {
        bookings[i] = bookings[i + 1];
    }

    bookingCount--;
    return true;
}

int BookingSystem::between(int day, int firstHour, int lastHour,
                           Booking result[], int capacity) const {
    int position = lowerBound(day, firstHour);
    int resultCount = 0;

    while (position < bookingCount && resultCount < capacity) {
        const Booking& current = bookings[position];

        if (current.day != day || current.startHour >= lastHour) {
            break;
        }

        result[resultCount] = current;
        resultCount++;
        position++;
    }

    return resultCount;
}

int BookingSystem::onDay(int day, Booking result[], int capacity) const {
    return between(day, 0, 24, result, capacity);
}

const Booking* BookingSystem::next(int day, int hour) const {
    int position = lowerBound(day, hour);

    if (position == bookingCount) {
        return nullptr;
    }

    return &bookings[position];
}

int BookingSystem::size() const {
    return bookingCount;
}
