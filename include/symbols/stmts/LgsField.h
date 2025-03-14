#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsType;
class LgsExpr;

class LgsField final : public LgsValue {
public:
    string name;
    string parentName;
    size_t fieldPosition;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    Value* gep = nullptr;

    LgsField(const string& name, const string& parentName, LgsType* type, const size_t fieldPosition, LgsExpr* expr) :
        name(name),
        parentName(parentName),
        fieldPosition(fieldPosition),
        type(type),
        expr(expr) {
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* lvalueExpr, LgsInstance* instance);
    ~LgsField() override = default;
};



#endif //LOGOSFIELD_H
