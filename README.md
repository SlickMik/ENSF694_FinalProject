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

## Demo Scenarios

Run `./campus`, then enter the numbers shown below. Each demo is separate — restart the app if you want a clean session.

### 1. Shortest path (two routes)

Main menu → `1` Navigation

**Route 1**
- `1` Find route
- Start: `1` (Library)
- Destination: `3` (ICT)
- Screenshot the path and travel time.

**Route 2**
- `1` Find route
- Start: `2` (Science A)
- Destination: `8` (MFH)
- Screenshot the path and travel time.

Do not undo yet. Stay in the Navigation menu.

### 2. Undo navigation

Still in Navigation (or start fresh: Main → `1`).

1. `1` Find route → `3` (ICT) → `9` (Residence)
2. `3` Previous routes — screenshot the list
3. `2` Undo — should print `Back to ICT`
4. `3` Previous routes again — last route should be gone
5. `4` Back to main menu

Undo removes the most recent route and returns its starting building.

### 3. Booking range query

Main menu → `2` Bookings → `4` Events in time range

```
Day number: 0
Start of range: 10
End of range: 14
```

Screenshot the events listed. Press `7` to return to the main menu.

(The app loads 100 sample bookings on startup.)

### 4. Priority service queue

Main menu → `3` Service desk

Add three requests in this order:

| Step | Choice | Input | Priority |
|------|--------|-------|----------|
| Add | `1` | Broken projector | `3` (Low) |
| Add | `1` | Network down | `1` (Emergency) |
| Add | `1` | Need markers | `2` (Standard) |

Then `2` Serve next three times. Order should be Emergency → Standard → Low. Screenshot each serve. Press `3` to go back.

### 5. Fast resource lookup

Main menu → `4` Resources → `1` Find

- Enter `ICT` — should show the record and table check count
- Enter `DOES_NOT_EXIST` — should show `Not found.`

Screenshot both. Press `4` to go back.

### 6. Request pipeline (20 requests)

Main menu → `5` Incoming requests → `4` Test 20 requests

Screenshot the processing order `1 -> 2 -> ... -> 20`. Press `5` to go back.


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
