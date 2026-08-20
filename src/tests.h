#pragma once

#include "booking.h"
#include "campus.h"
#include "lookup.h"
#include "navigation.h"

void runRequirementTests(const Campus& campus,
                         const Navigator& navigator,
                         const BookingSystem& bookingSystem,
                         const ResourceLookup& directory);
