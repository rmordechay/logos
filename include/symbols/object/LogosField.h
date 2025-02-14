#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "CodeGeneration.h"


class LogosType;
class LogosExpr;

class LogosField final : public CodeGeneration {
public:
    string name;
    string parentName;
    LogosType* inferredType = nullptr;
    LogosType* userType = nullptr;
    LogosExpr* expr = nullptr;

    LogosField(const string& name, const string& parentName, LogosType* inferredType, LogosExpr* expr) :
        name(name),
        parentName(parentName),
        inferredType(inferredType),
        expr(expr) {
    }

    Value* writeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosField() override = default;
};



#endif //LOGOSFIELD_H
