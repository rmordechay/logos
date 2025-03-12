#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LogosValue.h"

class LogosType;
class LogosExpr;

class LogosField final : public LogosValue {
public:
    string name;
    string parentName;
    size_t fieldPosition;
    LogosType* type = nullptr;
    LogosExpr* expr = nullptr;
    Value* gep = nullptr;

    LogosField(const string& name, const string& parentName, LogosType* type, const size_t fieldPosition, LogosExpr* expr) :
        name(name),
        parentName(parentName),
        fieldPosition(fieldPosition),
        type(type),
        expr(expr) {
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setFieldIRValue(CodeGenMetadata* metadata, LogosExpr* lvalueExpr, LogosInstance* instance);
    ~LogosField() override = default;
};



#endif //LOGOSFIELD_H
