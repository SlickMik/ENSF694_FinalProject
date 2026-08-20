#include "room.h"

bool Room::addBooking(const Booking& booking) {
    if (bookingCount == MAX_ROOM_BOOKINGS) return false;
    bookings[bookingCount++] = booking;
    return true;
}

bool Room::removeBooking(int day, int hour) {
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].day == day && bookings[i].startHour == hour) {
            for (int j = i; j < bookingCount - 1; j++) bookings[j] = bookings[j + 1];
            bookingCount--;
            return true;
        }
    }
    return false;
}
