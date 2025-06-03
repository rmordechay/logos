#ifndef LOGOSFIELD_H
#define LOGOSFIELD_H
#include "LgsValue.h"

class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField : public LgsValue {
public:
    std::string name;
    size_t position = 0;
    bool isPublic = false;
    bool isConst = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    LgsObject* parent = nullptr;

    LgsField(const std::string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), expr(expr), type(type) {}
    virtual Value* getGEP(LgsRuntime* runtime, Value* instance = nullptr);
    void setFieldIRValue(LgsRuntime* runtime, LgsExpr* expr, Value* instance = nullptr);
    LgsField* clone() const;
    nlohmann::json asJSON() override;
    ~LgsField() override;
};



#endif //LOGOSFIELD_H
