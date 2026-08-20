#pragma once

#include <string>

struct IncomingRequest {
    int number = 0;
    std::string type;
    std::string details;
    std::string source;
    std::string destination;
    int priority = 3;
};

class RequestPipeline {
    IncomingRequest requests[100];
    int front = 0;
    int back = 0;
    int requestCount = 0;

public:
    bool enqueue(const IncomingRequest& request);
    bool dequeue(IncomingRequest& request);
    int size() const;
};
