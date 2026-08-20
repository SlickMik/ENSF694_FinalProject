#include "booking.h"
#include "lookup.h"
#include "navigation.h"
#include "pipeline.h"
#include "service.h"
#include "tests.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

std::string mapFile() {
    const char* names[] = {"campus_map.csv", "FinalProject/campus_map.csv", "../FinalProject/campus_map.csv"};

    for (const char* name : names) {
        std::ifstream file(name);
        if (file) return name;
    }

    throw std::runtime_error("campus_map.csv not found");
}

void printRoute(const Route& route) {
    for (int i = 0; i < route.location_count; i++) {
        if (i > 0) std::cout << " -> ";
        std::cout << route.locations[i];
    }

    std::cout << "\nTravel time: " << route.cost << " minutes\n";
}

void printBooking(const Booking& booking) {
    std::cout << booking.room << " | Day " << booking.day << " | "
              << booking.startHour << ":00 - " << booking.endHour << ":00 | "
              << booking.title << "\n";
}

const char* priorityName(int priority) {
    if (priority == 1) return "Emergency";
    if (priority == 2) return "Standard";
    return "Low";
}

std::string chooseLocation(const Campus& campus, const char* message) {
    std::cout << "\n" << message << "\n";

    for (int i = 0; i < campus.building_count(); i++) {
        std::cout << i + 1 << ". " << campus.building(i).name << "\n";
    }

    int choice;
    std::cout << "Selection: ";
    std::cin >> choice;

    if (choice < 1 || choice > campus.building_count()) {
        return "";
    }

    return campus.building(choice - 1).name;
}

int chooseRoom(const Campus& campus) {
    for (int i = 0; i < campus.room_count(); i++) {
        std::cout << i + 1 << ". " << campus.room(i).roomId << "\n";
    }

    int choice;
    std::cout << "Select room: ";
    std::cin >> choice;

    if (choice < 1 || choice > campus.room_count()) {
        return -1;
    }

    return choice - 1;
}

void navigationMenu(const Campus& campus, NavigationSession& session) {
    while (true) {
        std::cout << "\nNavigation\n"
                     "1. Find route\n"
                     "2. Undo route\n"
                     "3. Previous routes\n"
                     "4. Back\n"
                     "Choice: ";

        int choice;
        std::cin >> choice;

        try {
            if (choice == 1) {
                std::string source = chooseLocation(campus, "Where are you starting?");
                std::string destination = chooseLocation(campus, "Where are you going?");

                if (source.empty() || destination.empty()) {
                    std::cout << "Invalid location.\n";
                    continue;
                }

                Route route = session.navigate(source, destination);
                std::cout << "Route: ";
                printRoute(route);
            } else if (choice == 2) {
                std::cout << "Back to " << session.undo() << "\n";
            } else if (choice == 3) {
                if (session.history_size() == 0) {
                    std::cout << "History is empty.\n";
                } else {
                    for (int i = 0; i < session.history_size(); i++) {
                        const Route& route = session.getRoute(i);
                        std::cout << i + 1 << ". " << route.source << " -> "
                                  << route.destination << " | " << route.cost
                                  << " minutes\n";
                    }
                }
            } else if (choice == 4) {
                return;
            } else {
                std::cout << "Invalid choice.\n";
            }
        } catch (const std::exception& error) {
            std::cout << error.what() << "\n";
        }
    }
}

void bookingMenu(BookingSystem& bookingSystem, Campus& campus) {
    while (true) {
        std::cout << "\nBookings\n"
                     "1. Add booking\n"
                     "2. Remove booking\n"
                     "3. Find booking\n"
                     "4. Events in time range\n"
                     "5. Next event\n"
                     "6. Events on a day\n"
                     "7. Back\n"
                     "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            Booking booking;

            std::cout << "Event name: ";
            std::getline(std::cin >> std::ws, booking.title);
            std::cout << "Day number (0 is today): ";
            std::cin >> booking.day;
            std::cout << "Start hour (0-23): ";
            std::cin >> booking.startHour;
            std::cout << "End hour (1-24): ";
            std::cin >> booking.endHour;

            int available[10];
            int availableCount = 0;

            std::cout << "\nAvailable rooms:\n";
            for (int i = 0; i < campus.room_count(); i++) {
                if (bookingSystem.isAvailable(campus.room(i).roomId, booking.day,
                                              booking.startHour, booking.endHour)) {
                    available[availableCount] = i;
                    std::cout << availableCount + 1 << ". " << campus.room(i).roomId
                              << " | capacity " << campus.room(i).capacity
                              << " | " << campus.room(i).roomType << "\n";
                    availableCount++;
                }
            }

            if (availableCount == 0) {
                std::cout << "No rooms available.\n";
                continue;
            }

            int roomChoice;
            std::cout << "Select room: ";
            std::cin >> roomChoice;

            if (roomChoice < 1 || roomChoice > availableCount) {
                std::cout << "Invalid room selection.\n";
                continue;
            }

            booking.room = campus.room(available[roomChoice - 1]).roomId;

            if (bookingSystem.add(booking)) {
                std::cout << "Added: ";
                printBooking(booking);
            } else {
                std::cout << "Could not add booking.\n";
            }
        } else if (choice == 2 || choice == 3) {
            std::cout << "\nRooms:\n";
            int roomChoice = chooseRoom(campus);

            if (roomChoice < 0) {
                std::cout << "Invalid room selection.\n";
                continue;
            }

            int day, hour;
            std::cout << "Day number: "; std::cin >> day;
            std::cout << "Starting hour: "; std::cin >> hour;

            if (choice == 2) {
                if (bookingSystem.remove(campus.room(roomChoice).roomId, day, hour))
                    std::cout << "Booking removed.\n";
                else
                    std::cout << "Booking not found.\n";
            } else {
                const Booking* booking = bookingSystem.get(campus.room(roomChoice).roomId, day, hour);
                if (booking) printBooking(*booking);
                else std::cout << "Booking not found.\n";
            }
        } else if (choice == 4) {
            int day, firstHour, lastHour;
            std::cout << "Day number: "; std::cin >> day;
            std::cout << "Start of range: "; std::cin >> firstHour;
            std::cout << "End of range: "; std::cin >> lastHour;

            Booking result[MAX_BOOKINGS];
            int count = bookingSystem.between(day, firstHour, lastHour, result, MAX_BOOKINGS);
            for (int i = 0; i < count; i++) printBooking(result[i]);
            if (count == 0) std::cout << "No events found.\n";
        } else if (choice == 5) {
            int day, hour;
            std::cout << "Current day number: "; std::cin >> day;
            std::cout << "Current hour: "; std::cin >> hour;

            const Booking* booking = bookingSystem.next(day, hour);
            if (booking) {
                std::cout << "\nNext event:\n";
                printBooking(*booking);
            } else {
                std::cout << "No upcoming events.\n";
            }
        } else if (choice == 6) {
            int day;
            std::cout << "Day number: "; std::cin >> day;

            Booking result[MAX_BOOKINGS];
            int count = bookingSystem.onDay(day, result, MAX_BOOKINGS);

            std::cout << "\nEvents on day " << day << ":\n";
            for (int i = 0; i < count; i++) printBooking(result[i]);
            if (count == 0) std::cout << "No events found.\n";
        } else if (choice == 7) {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void serviceMenu(ServiceQueue& serviceQueue) {
    while (true) {
        std::cout << "\nService desk\n"
                     "1. Add request\n"
                     "2. Serve next\n"
                     "3. Back\n"
                     "Waiting requests: " << serviceQueue.size() << "\n"
                     "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            ServiceRequest request;
            std::cout << "Describe the problem: ";
            std::getline(std::cin >> std::ws, request.description);

            std::cout << "\nUrgency:\n"
                         "1. Emergency\n"
                         "2. Standard\n"
                         "3. Low\n"
                         "Selection: ";
            std::cin >> request.priority;

            if (serviceQueue.add(request))
                std::cout << priorityName(request.priority) << " request added.\n";
            else
                std::cout << "Could not add request.\n";
        } else if (choice == 2) {
            ServiceRequest request;

            if (serviceQueue.serve(request)) {
                std::cout << "\nNow serving:\n"
                          << priorityName(request.priority) << " - " << request.description << "\n";
            } else {
                std::cout << "Queue is empty.\n";
            }
        } else if (choice == 3) {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void resourceMenu(ResourceLookup& directory) {
    while (true) {
        std::cout << "\nResources\n"
                     "1. Find\n"
                     "2. Add\n"
                     "3. Remove\n"
                     "4. Back\n"
                     "Stored records: " << directory.size() << "\n"
                     "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string id;
            std::cout << "Resource ID: ";
            std::cin >> id;

            int checks;
            const Resource* resource = directory.find(id, checks);

            if (resource) {
                std::cout << resource->id << " | " << resource->name
                          << " | " << resource->type << "\n";
                std::cout << "Table checks: " << checks << "\n";
            } else {
                std::cout << "Not found.\n";
            }
        } else if (choice == 2) {
            Resource resource;
            std::cout << "Unique ID: ";
            std::cin >> resource.id;
            std::cout << "Name: ";
            std::getline(std::cin >> std::ws, resource.name);
            std::cout << "Type (Building, Room, or Service): ";
            std::getline(std::cin >> std::ws, resource.type);

            if (directory.insert(resource))
                std::cout << "Added.\n";
            else
                std::cout << "ID already exists or table is full.\n";
        } else if (choice == 3) {
            std::string id;
            std::cout << "Resource ID to delete: ";
            std::cin >> id;

            if (directory.remove(id))
                std::cout << "Removed.\n";
            else
                std::cout << "Not found.\n";
        } else if (choice == 4) {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void pipelineMenu(RequestPipeline& pipeline, const Campus& campus,
                  const Navigator& navigator, ServiceQueue& serviceQueue) {
    int nextNumber = 1;

    while (true) {
        std::cout << "\nIncoming requests\n"
                     "1. Add navigation request\n"
                     "2. Add service request\n"
                     "3. Process next\n"
                     "4. Test 20 requests\n"
                     "5. Back\n"
                     "Waiting requests: " << pipeline.size() << "\n"
                     "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            IncomingRequest request;
            request.number = nextNumber;

            if (choice == 1) {
                // Save both buildings so the route can be found later
                request.type = "Navigation";
                request.source = chooseLocation(campus, "Starting location:");
                request.destination = chooseLocation(campus, "Destination:");

                if (request.source.empty() || request.destination.empty()) {
                    std::cout << "Invalid location.\n";
                    continue;
                }

                request.details = request.source + " to " + request.destination;
            } else {
                request.type = "Service";
                std::cout << "Describe the problem: ";
                std::getline(std::cin >> std::ws, request.details);
                std::cout << "Priority (1 Emergency, 2 Standard, 3 Low): ";
                std::cin >> request.priority;

                if (request.priority < 1 || request.priority > 3) {
                    std::cout << "Invalid priority.\n";
                    continue;
                }
            }

            if (pipeline.enqueue(request)) {
                std::cout << "Request " << request.number << " added.\n";
                nextNumber++;
            } else {
                std::cout << "Queue is full.\n";
            }
        } else if (choice == 3) {
            IncomingRequest request;

            if (pipeline.dequeue(request)) {
                std::cout << "Processing request " << request.number << ": "
                          << request.type << " - " << request.details << "\n";

                // Do the actual job after it comes out of the pipeline
                if (request.type == "Navigation") {
                    try {
                        Route route = navigator.shortest_path(campus, request.source,
                                                              request.destination);
                        std::cout << "Route: ";
                        printRoute(route);
                    } catch (const std::exception& error) {
                        std::cout << "Navigation failed: " << error.what() << "\n";
                    }
                } else if (request.type == "Service") {
                    // Service requests go to the priority queue next
                    if (serviceQueue.add({request.details, request.priority}))
                        std::cout << "Sent to the service desk queue.\n";
                    else
                        std::cout << "Service desk queue is full.\n";
                }
            } else {
                std::cout << "Queue is empty.\n";
            }
        } else if (choice == 4) {
            RequestPipeline testPipeline;

            for (int i = 1; i <= 20; i++) {
                std::string type = i % 2 == 0 ? "Service" : "Navigation";
                testPipeline.enqueue({i, type, "Test request " + std::to_string(i)});
            }

            std::cout << "\nProcessing order:\n";
            for (int i = 1; i <= 20; i++) {
                IncomingRequest request;
                testPipeline.dequeue(request);
                std::cout << request.number;
                if (i < 20) std::cout << " -> ";
            }
            std::cout << "\nAll 20 requests were processed in arrival order.\n";
        } else if (choice == 5) {
            return;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

int main() {
    try {
        Campus campus;
        campus.load(mapFile());

        if (campus.building_count() < 15 || campus.edge_count() < 25) {
            throw std::runtime_error("campus map is too small");
        }

        Navigator navigator;
        NavigationSession session(campus, navigator);
        campus.addRoom("ICT", {"ICT101", 40, "lecture"});
        campus.addRoom("ICT", {"ICT102", 30, "lab"});
        campus.addRoom("ENG Block", {"ENG201", 50, "lecture"});
        campus.addRoom("Library", {"LIB101", 12, "study"});
        campus.addRoom("Science A", {"SCI301", 25, "lab"});

        BookingSystem bookingSystem(&campus);
        ServiceQueue serviceQueue;
        ResourceLookup directory;
        RequestPipeline pipeline;

        // Add some starting bookings for the demo
        for (int i = 0; i < 100; i++) {
            bookingSystem.add({campus.room(i % campus.room_count()).roomId,
                               "Event " + std::to_string(i),
                               i / 20, i % 20, i % 20 + 1});
        }

        // Put buildings and rooms into the lookup table
        for (int i = 0; i < campus.building_count(); i++) {
            std::string id = campus.building(i).name;
            directory.insert({id, id, "Building"});
        }

        for (int i = 0; i < campus.room_count(); i++) {
            directory.insert({campus.room(i).roomId, campus.room(i).roomId, "Room"});
        }

        std::cout << "Campus Services\n";

        while (true) {
            std::cout << "\nMain menu\n"
                         "1. Navigation\n"
                         "2. Bookings\n"
                         "3. Service desk\n"
                         "4. Resources\n"
                         "5. Incoming requests\n"
                         "6. Run tests\n"
                         "7. Exit\n"
                         "Choice: ";

            int choice;
            if (!(std::cin >> choice)) break;

            if (choice == 1)
                navigationMenu(campus, session);
            else if (choice == 2)
                bookingMenu(bookingSystem, campus);
            else if (choice == 3)
                serviceMenu(serviceQueue);
            else if (choice == 4)
                resourceMenu(directory);
            else if (choice == 5)
                pipelineMenu(pipeline, campus, navigator, serviceQueue);
            else if (choice == 6)
                runRequirementTests(campus, navigator, bookingSystem, directory);
            else if (choice == 7) {
                std::cout << "Goodbye.\n";
                break;
            } else
                std::cout << "Invalid choice.\n";
        }

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "ERROR: " << error.what() << "\n";
        return 1;
    }
}
