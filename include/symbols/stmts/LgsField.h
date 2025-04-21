#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField : public LgsValue {
public:
    string name;
    size_t position;
    bool isPublic = false;
    bool isConst = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    LgsType* userType = nullptr;
    LgsObject* parent = nullptr;

    LgsField(const string& name, const size_t position, LgsType* userType, LgsExpr* expr = nullptr) : name(name), position(position), userType(userType), expr(expr) {}
    virtual Value* getIRValue(CodeGenMetadata* metadata);
    void setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* expr) const;
    Value* getGEP(CodeGenMetadata* metadata) const;
    json asJSON() override;
    ~LgsField() override = default;
};



#endif //LOGOSFIELD_H
