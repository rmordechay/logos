#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LogosValue.h"

class LogosType;
class LogosExpr;

class LogosField final : public LogosValue {
public:
    string name;
    size_t fieldPosition;
    LogosObject* parentObj = nullptr;
    LogosType* type = nullptr;
    LogosType* userType = nullptr;
    LogosExpr* expr = nullptr;

    LogosField(const string& name, LogosObject* parentObj, LogosType* inferredType, LogosExpr* expr, const size_t fieldPosition) :
        name(name),
        fieldPosition(fieldPosition),
        parentObj(parentObj),
        type(inferredType),
        expr(expr) {
    }

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosField() override = default;
};



#endif //LOGOSFIELD_H
