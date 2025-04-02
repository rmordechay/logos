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
    LgsType* userType = nullptr;
    LgsExpr* expr = nullptr;
    Value* gep = nullptr;
    LgsExpr* parentExpr = nullptr;

    LgsField(const string& name, const string& parentName, const size_t fieldPosition, LgsType* type, LgsExpr* expr = nullptr) : name(name), parentName(parentName), fieldPosition(fieldPosition), type(type), expr(expr) {}
    LgsField(const string& name, const size_t fieldPosition, LgsType* type, LgsExpr* expr) : LgsField(name, "", fieldPosition, type, expr) {}
    Value* getIRValue(CodeGenMetadata* metadata);
    Value* createIRValue(CodeGenMetadata* metadata);
    Value* getGEP(CodeGenMetadata* metadata);
    void setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr);
    ~LgsField() override = default;
};



#endif //LOGOSFIELD_H
