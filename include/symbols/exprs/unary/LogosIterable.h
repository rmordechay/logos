#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H

#include <cstddef>

class LogosIterable {
public:
    virtual size_t size() = 0;
    virtual ~LogosIterable() = default;
};

#endif //LOGOSITERABLE_H
