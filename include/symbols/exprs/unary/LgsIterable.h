#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H

#include <cstddef>
struct CodeGenMetadata;

class LgsIterable {
public:
    virtual size_t size() = 0;
    virtual ~LgsIterable() = default;
};

#endif //LOGOSITERABLE_H
