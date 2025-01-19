#ifndef LOGOSUSERTYPE_H
#define LOGOSUSERTYPE_H
#include "LogosType.h"

class LogosUserType final : public LogosType {
public:
    std::string name;
    explicit LogosUserType(const std::string& name) : name(name) {}
    Type* getLLVMType(IRBuilder<>* builder) const override {
        return nullptr;
    }
    ~LogosUserType() override = default;
};


#endif //LOGOSUSERTYPE_H
