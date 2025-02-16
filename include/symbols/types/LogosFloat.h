#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "CodeGeneration.h"
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    Type* llvmType = Type::getFloatTy(context);
     string typeName = "Float";

    const string name() const override;
    Type* getLLVMType() override;
    bool operator==(LogosType* other) const override;
    ~LogosFloat() override = default;
};

inline const string LogosFloat::name() const {
    return typeName;
}

inline Type* LogosFloat::getLLVMType() {
    return llvmType;
}

inline bool LogosFloat::operator==(LogosType* other) const { return true;
}


#endif //LOGOSFLOAT_H
