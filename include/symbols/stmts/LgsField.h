#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsType;
class LogosExpr;

class LgsField final : public LgsValue {
public:
    string name;
    string parentName;
    size_t fieldPosition;
    LgsType* type = nullptr;
    LogosExpr* expr = nullptr;
    Value* gep = nullptr;

    LgsField(const string& name, const string& parentName, LgsType* type, const size_t fieldPosition, LogosExpr* expr) :
        name(name),
        parentName(parentName),
        fieldPosition(fieldPosition),
        type(type),
        expr(expr) {
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setFieldIRValue(CodeGenMetadata* metadata, LogosExpr* lvalueExpr, LgsInstance* instance);
    ~LgsField() override = default;
};



#endif //LOGOSFIELD_H
