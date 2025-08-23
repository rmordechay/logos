#pragma once
#include "LgsObject.h"
#include "LgsType.h"

class LgsInterface final : public LgsObject {
public:
    explicit LgsInterface(const std::string& name) : LgsObject(name) {}
    std::string pname() override;
    json::value asJSON() override;
    std::string getName() override;
    llvm::Type* getIRType(LgsCodeGen& codeGen) override;
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    size_t getSizeBytes() override;
    ~LgsInterface() override;
};
