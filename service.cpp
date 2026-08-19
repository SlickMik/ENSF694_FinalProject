#include "service.h"

bool ServiceQueue::add(const ServiceRequest& request) {
    if (requestCount == 100 || request.priority < 1 || request.priority > 3) {
        return false;
    }

    requests[requestCount] = request;
    requestCount++;
    return true;
}

bool ServiceQueue::serve(ServiceRequest& request) {
    if (requestCount == 0) {
        return false;
    }

    int highest = 0;

    for (int i = 1; i < requestCount; i++) {
        if (requests[i].priority < requests[highest].priority) {
            highest = i;
        }
    }

    request = requests[highest];

    for (int i = highest; i < requestCount - 1; i++) {
        requests[i] = requests[i + 1];
    }

    requestCount--;
    return true;
}

int ServiceQueue::size() const {
    return requestCount;
}
