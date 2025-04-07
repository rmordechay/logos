#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsType;
class LgsExpr;

class LgsField : public LgsValue {
public:
    string name;
    size_t position;
    LgsType* type = nullptr;
    LgsType* userType = nullptr;
    LgsExpr* expr = nullptr;
    Value* gep = nullptr;
    LgsExpr* parentExpr = nullptr;

    LgsField(const string& name, const size_t position, LgsType* type, LgsExpr* expr = nullptr) : name(name), position(position), type(type), expr(expr) {}
    Value* getIRValue(CodeGenMetadata* metadata);
    virtual Value* createIRValue(CodeGenMetadata* metadata);
    Value* getGEP(CodeGenMetadata* metadata);
    void setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr);
    ~LgsField() override = default;
};



#endif //LOGOSFIELD_H
