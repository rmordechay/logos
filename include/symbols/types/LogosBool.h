#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "CodeGeneration.h"
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    Type* llvmType = Type::getInt1Ty(context);
     string typeName = "Bool";
     auto trueLiteral = "true";

    const string name() const override;
    Type* getLLVMType() override;
    bool operator==(LogosType* other) const override;
    ~LogosBool() override = default;
};

inline const string LogosBool::name() const {
    return typeName;
}

inline void LogosBool::setLLVMType(Type* type) {

}

inline Type* LogosBool::getLLVMType() {
    return llvmType;
}

inline bool LogosBool::operator==(LogosType* other) const { return true;
    return true;
}

#endif //LOGOSBOOL_H
