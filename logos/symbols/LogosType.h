#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include "LogosParser.h"

class LogosType {
public:
    virtual std::string getName() const = 0;
    virtual ~LogosType() = default;
};

#endif //LOGOSTYPE_H
