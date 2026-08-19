#include "navigation.h"
#include <climits>
#include <stdexcept>

Route Navigator::shortest_path(const Campus& campus, const std::string& source,
                               const std::string& destination) const {
    int start = campus.find(source), finish = campus.find(destination);
    if (start < 0 || finish < 0) throw std::out_of_range("unknown building");

    int distance[MAX_BUILDINGS], previous[MAX_BUILDINGS];
    bool visited[MAX_BUILDINGS]{};
    for (int i = 0; i < MAX_BUILDINGS; ++i) { distance[i] = INT_MAX; previous[i] = -1; }
    distance[start] = 0;

    for (int step = 0; step < campus.building_count(); ++step) {
        int current = -1;
        for (int i = 0; i < campus.building_count(); ++i)
            if (!visited[i] && (current < 0 || distance[i] < distance[current])) current = i;
        if (current < 0 || distance[current] == INT_MAX) break;
        visited[current] = true;
        for (int next = 0; next < campus.building_count(); ++next) {
            int weight = campus.weight(current, next);
            if (weight && distance[current] + weight < distance[next]) {
                distance[next] = distance[current] + weight;
                previous[next] = current;
            }
        }
    }

    if (distance[finish] == INT_MAX) throw std::runtime_error("no route");
    int reverse[MAX_BUILDINGS], reverse_count = 0;
    for (int at = finish; at >= 0; at = previous[at]) reverse[reverse_count++] = at;
    Route route;
    route.source = source; route.destination = destination; route.cost = distance[finish];
    while (reverse_count) route.locations[route.location_count++] = campus.building(reverse[--reverse_count]).name;
    return route;
}

NavigationSession::NavigationSession(const Campus& campus, const Navigator& navigator)
    : campus(campus), navigator(navigator) {}
Route NavigationSession::navigate(const std::string& source, const std::string& destination) {
    if (historyCount == 10) throw std::overflow_error("history full");
    Route route = navigator.shortest_path(campus, source, destination);
    history[historyCount++] = route;
    return route;
}
std::string NavigationSession::undo() {
    if (!historyCount) throw std::underflow_error("history empty");
    return history[--historyCount].source;
}
int NavigationSession::history_size() const { return historyCount; }
