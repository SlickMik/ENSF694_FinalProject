#include "tests.h"
#include "pipeline.h"
#include "service.h"
#include <iostream>

void runRequirementTests(const Campus& campus,
                         const Navigator& navigator,
                         const BookingSystem& bookingSystem,
                         const ResourceLookup& directory) {
    std::cout << "\nQuick requirement checks\n";

    // 2.1 map size + one shortest path
    bool mapOk = campus.building_count() >= 15 && campus.edge_count() >= 25;
    std::cout << "2.1 Map (" << campus.building_count() << " buildings, "
              << campus.edge_count() << " edges): " << (mapOk ? "ok" : "fail") << "\n";

    bool pathOk = false;
    if (campus.building_count() >= 2) {
        try {
            Route route = navigator.shortest_path(campus, campus.building(0).name,
                                                  campus.building(1).name);
            pathOk = route.location_count > 0 && route.cost > 0;
            std::cout << "    Shortest path: " << (pathOk ? "ok" : "fail")
                      << " (" << route.cost << " min)\n";
        } catch (...) {
            std::cout << "    Shortest path: fail\n";
        }
    }

    // 2.2 undo
    bool undoOk = false;
    if (campus.building_count() >= 3) {
        try {
            NavigationSession session(campus, navigator);
            session.navigate(campus.building(0).name, campus.building(1).name);
            session.navigate(campus.building(1).name, campus.building(2).name);
            undoOk = session.undo() == campus.building(1).name;
        } catch (...) {}
    }
    std::cout << "2.2 Undo: " << (undoOk ? "ok" : "fail") << "\n";

    // 2.3 bookings
    std::cout << "2.3 Bookings (" << bookingSystem.size() << " loaded): "
              << (bookingSystem.size() >= 100 ? "ok" : "fail") << "\n";

    // 2.4 priority queue
    ServiceQueue queue;
    queue.add({"low", 3});
    queue.add({"emergency", 1});
    queue.add({"standard", 2});
    ServiceRequest req;
    bool priorityOk = queue.serve(req) && req.priority == 1
                   && queue.serve(req) && req.priority == 2
                   && queue.serve(req) && req.priority == 3;
    std::cout << "2.4 Priority queue: " << (priorityOk ? "ok" : "fail") << "\n";

    // 2.5 lookup
    int checks = 0;
    bool lookupOk = directory.find(campus.building(0).name, checks) != nullptr
                 && directory.find("NOT_A_KEY", checks) == nullptr;
    std::cout << "2.5 Lookup: " << (lookupOk ? "ok" : "fail") << "\n";

    // 2.6 pipeline (20 requests in order)
    RequestPipeline pipeline;
    bool pipeOk = true;
    for (int i = 1; i <= 20 && pipeOk; i++) {
        pipeOk = pipeline.enqueue({i, "Test", "req " + std::to_string(i)});
    }
    for (int i = 1; i <= 20 && pipeOk; i++) {
        IncomingRequest req;
        pipeOk = pipeline.dequeue(req) && req.number == i;
    }
    std::cout << "2.6 Pipeline (20 requests): " << (pipeOk ? "ok" : "fail") << "\n";

    std::cout << "\nUse menus 1-5 for full demos / report screenshots.\n";
}
