#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "../types/LogosType.h"

class LogosFunc {
public:
    std::string name;
    const LogosType& type;

    explicit LogosFunc(const std::string& name, const LogosType& funcType) : name(name), type(funcType) {}
    virtual ~LogosFunc() = default;
};

#endif //LOGOSFUNC_H
