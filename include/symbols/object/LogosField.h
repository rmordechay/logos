#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "CodeGeneration.h"


class LogosType;
class LogosExpr;

class LogosField final : public CodeGeneration {
public:
    string name;
    string parentName;
    size_t fieldPosition;
    LogosType* inferredType = nullptr;
    LogosType* userType = nullptr;
    LogosExpr* expr = nullptr;

    LogosField(const string& name, const string& parentName, LogosType* inferredType, LogosExpr* expr, const size_t fieldPosition) :
        name(name),
        parentName(parentName),
        fieldPosition(fieldPosition),
        inferredType(inferredType),
        expr(expr) {
    }

    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosField() override = default;
};



#endif //LOGOSFIELD_H
