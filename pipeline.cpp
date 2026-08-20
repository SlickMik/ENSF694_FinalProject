#include "pipeline.h"

bool RequestPipeline::enqueue(const IncomingRequest& request) {
    if (requestCount == 100) {
        return false;
    }

    requests[back] = request;
    back = (back + 1) % 100;
    requestCount++;
    return true;
}

bool RequestPipeline::dequeue(IncomingRequest& request) {
    if (requestCount == 0) {
        return false;
    }

    request = requests[front];
    front = (front + 1) % 100;
    requestCount--;
    return true;
}

int RequestPipeline::size() const {
    return requestCount;
}
