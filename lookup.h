#pragma once

#include <string>

struct Resource {
    std::string id;
    std::string name;
    std::string type;
};

class ResourceLookup {
    struct Entry {
        Resource resource;
        bool used = false;
        bool active = false;
    };

    Entry table[257];
    int resourceCount = 0;

    int hash(const std::string& id) const;

public:
    bool insert(const Resource& resource);
    bool remove(const std::string& id);
    const Resource* find(const std::string& id) const;
    const Resource* find(const std::string& id, int& checks) const;
    int size() const;
};
