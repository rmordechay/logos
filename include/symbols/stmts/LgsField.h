#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField : public LgsValue {
public:
    string name;
    size_t position = 0;
    bool isPublic = false;
    bool isConst = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    LgsObject* parent = nullptr;

    LgsField(const string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), expr(expr), type(type) {}
    virtual Value* getGEP(CodegenMetadata* metadata, Value* instance = nullptr);
    void setFieldIRValue(CodegenMetadata* metadata, LgsExpr* expr, Value* instance = nullptr);
    LgsField* clone() const;
    json asJSON() override;
    ~LgsField() override;
};



#endif //LOGOSFIELD_H
