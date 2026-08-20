# Campus Navigation and Event Management System

ENSF 694 – Data Structures and Algorithms (Summer 2026)

C++ console app. Campus is a weighted graph (buildings + walking times). You can find shortest paths, undo routes, book rooms, handle service requests by priority, look up buildings/rooms, and process incoming requests in order.

## Group Members

- Muhammad Ibrahim Khan
- Saman Pordanesh

## GitHub

https://github.com/SlickMik/ENSF694_FinalProject.git

## Build and Run

Needs `campus_map.csv` in the same folder as the executable.

```bash
g++ -std=c++17 -o campus main.cpp campus.cpp navigation.cpp building.cpp room.cpp booking.cpp service.cpp lookup.cpp pipeline.cpp tests.cpp
./campus
```

## Map File

`campus_map.csv` — one undirected edge per line:

```
BuildingA,BuildingB,minutes
```

Lines starting with `#` are comments. Current map has 15 buildings and 25 edges (spec sample plus extras to meet the size requirement).

## Features

1. **Navigation** — load map, Dijkstra shortest path, print route and total minutes.
2. **Undo** — session history, up to 10 routes. Undo drops the last query and returns its origin.
3. **Bookings** — add/remove/find, range query, next event, events on a day. Starts with 100 bookings.
4. **Service desk** — priority queue (1 Emergency, 2 Standard, 3 Low). Highest urgency served first.
5. **Resources** — hash table lookup by ID. Insert, delete, find (including missing keys).
6. **Incoming requests** — FIFO pipeline. Menu option 4 enqueues and processes 20 requests in arrival order.

Menu 6 runs a short ok/fail check. Use menus 1–5 for the report demos.

## Files

```
main.cpp            menus
campus.h/cpp        graph + load map
navigation.h/cpp    shortest path + undo
building.h/cpp      buildings and rooms
room.h/cpp          room bookings
booking.h/cpp       booking system
service.h/cpp       priority queue
lookup.h/cpp        hash table
pipeline.h/cpp      FIFO queue
tests.h/cpp         requirement check
campus_map.csv      campus graph
```
