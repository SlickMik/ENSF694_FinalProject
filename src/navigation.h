#pragma once

#include "campus.h"

struct Route {
    std::string source, destination;
    std::string locations[MAX_BUILDINGS];
    int location_count = 0;
    int cost = 0;
};

// Finds the cheapest route through the campus graph
class Navigator {
public:
    Route shortest_path(const Campus& campus, const std::string& source, const std::string& destination) const;
};

// Saves the last ten routes so they can be undone
class NavigationSession {
    const Campus& campus;
    const Navigator& navigator;
    Route history[10];
    int historyCount = 0;
public:
    NavigationSession(const Campus& campus, const Navigator& navigator);
    Route navigate(const std::string& source, const std::string& destination);
    std::string undo();
    int history_size() const;
    const Route& getRoute(int index) const;
};
