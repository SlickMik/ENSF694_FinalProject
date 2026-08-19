# Campus Navigation and Event Management System

ENSF 694 – Data Structures and Algorithms (Summer 2026)  
University of Calgary

A C++ console app for navigating a campus map, managing room bookings, and handling service requests. Buildings are nodes on a weighted graph; pathways are edges with walking time in minutes.

## Group Members

- Muhammad Ibrahim Khan
- Saman Pordanesh

## GitHub

https://github.com/SlickMik/ENSF694_FinalProject.git

## Build and Run

<need to be complete>

No `main.cpp` or build file yet. Once added:

```bash
g++ -std=c++17 -o campus campus.cpp navigation.cpp main.cpp
./campus
```

## Campus Map File

Load edges from a CSV file. One edge per line:

```
BuildingA,BuildingB,minutes
```

Lines starting with `#` are ignored. Example map from the project spec: Library, Science A, ICT, ENG Block, Gym, Student U, Parkade, MFH, Residence (15+ nodes, 25+ edges).

<need to be complete — sample map file not included yet>

## Features

### 2.1 Campus Map and Shortest Path (in progress)

- Campus stored as adjacency matrix (`Campus` in `campus.h`)
- Map loading from file works (`Campus::load`)
- Shortest path query: <need to be complete> (`Navigator::shortest_path` declared in `navigation.h`, no `.cpp` yet)

### 2.2 Route History and Undo (in progress)

- Session history holds up to 10 routes (`NavigationSession` in `navigation.h`)
- Navigate and undo: <need to be complete> (no implementation yet)

### 2.3 Room and Event Booking

<need to be complete>

### 2.4 Priority Service Queue

<need to be complete>

### 2.5 Fast Building Lookup

<need to be complete>

### 2.6 Request Processing Pipeline

<need to be complete>

### 2.7 Bonus: Balanced Event Index

<need to be complete>

## Project Structure

```
building.h      — Building struct
campus.h/cpp    — campus graph, load from file
navigation.h    — shortest path + session undo (headers only)
```

## Demo Scenarios

<need to be complete>

Report screenshots will cover: shortest path queries, undo navigation, booking range query, priority queue, fast lookup, and request pipeline (20+ requests).
