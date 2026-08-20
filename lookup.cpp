#include "lookup.h"

int ResourceLookup::hash(const std::string& id) const {
    unsigned int value = 0;

    for (char letter : id) {
        value = value * 31 + letter;
    }

    return value % 257;
}

bool ResourceLookup::insert(const Resource& resource) {
    int start = hash(resource.id);
    int deletedSpot = -1;

    for (int i = 0; i < 257; i++) {
        int position = (start + i) % 257;

        if (table[position].active && table[position].resource.id == resource.id) {
            return false;
        }

        if (table[position].used && !table[position].active && deletedSpot == -1) {
            deletedSpot = position;
        }

        if (!table[position].used) {
            if (deletedSpot != -1) position = deletedSpot;

            table[position].resource = resource;
            table[position].used = true;
            table[position].active = true;
            resourceCount++;
            return true;
        }
    }

    if (deletedSpot != -1) {
        table[deletedSpot].resource = resource;
        table[deletedSpot].active = true;
        resourceCount++;
        return true;
    }

    return false;
}

const Resource* ResourceLookup::find(const std::string& id, int& checks) const {
    int start = hash(id);
    checks = 0;

    for (int i = 0; i < 257; i++) {
        int position = (start + i) % 257;
        checks++;

        if (!table[position].used) {
            return nullptr;
        }

        if (table[position].active && table[position].resource.id == id) {
            return &table[position].resource;
        }
    }

    return nullptr;
}

const Resource* ResourceLookup::find(const std::string& id) const {
    int checks;
    return find(id, checks);
}

bool ResourceLookup::remove(const std::string& id) {
    int start = hash(id);

    for (int i = 0; i < 257; i++) {
        int position = (start + i) % 257;

        if (!table[position].used) {
            return false;
        }

        if (table[position].active && table[position].resource.id == id) {
            table[position].active = false;
            resourceCount--;
            return true;
        }
    }

    return false;
}

int ResourceLookup::size() const {
    return resourceCount;
}