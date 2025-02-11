#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "CodeGeneration.h"


class LogosType;
class LogosExpr;

class LogosField final : public CodeGeneration {
public:
    string name;
    LogosType* inferredType = nullptr;
    LogosType* userType = nullptr;
    LogosExpr* expr = nullptr;

    LogosField(const string& name, LogosType* inferredType, LogosExpr* expr) :
        name(name),
        inferredType(inferredType),
        expr(expr) {
    }

    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosField() override = default;
};



#endif //LOGOSFIELD_H
