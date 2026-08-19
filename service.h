#pragma once

#include <string>

struct ServiceRequest {
    std::string description;
    int priority = 3;
};

class ServiceQueue {
    ServiceRequest requests[100];
    int requestCount = 0;

public:
    bool add(const ServiceRequest& request);
    bool serve(ServiceRequest& request);
    int size() const;
};
