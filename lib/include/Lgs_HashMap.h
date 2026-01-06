#pragma once

struct Lgs_HashMap {
    void** entries;
    size_t len;
    size_t capacity;
};
