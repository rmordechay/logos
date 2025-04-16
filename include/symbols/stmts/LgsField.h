#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsType;
class LgsExpr;

class LgsField : public LgsValue {
public:
    string name;
    size_t position;
    bool isPublic = false;
    bool isConst = false;
    LgsType* type = nullptr;
    LgsType* userType = nullptr;
    LgsExpr* expr = nullptr;
    LgsObject* parent = nullptr;
    Value* parentIRValue = nullptr;
    Type* parentIRType = nullptr;

    LgsField(const string& name, const size_t position, LgsType* userType, LgsExpr* expr = nullptr) : name(name), position(position), userType(userType), expr(expr) {}
    Value* getIRValue(CodeGenMetadata* metadata);
    virtual Value* createIRValue(CodeGenMetadata* metadata);
    void setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr) const;
    Value* getGEP(CodeGenMetadata* metadata) const;
    ~LgsField() override = default;
};



#endif //LOGOSFIELD_H
