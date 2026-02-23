#pragma once
#include <string>

#include "LgsObject.h"
#include "LgsValue.h"

class LgsInterface final : public LgsObject {
public:
    explicit LgsInterface(const std::string& name) : LgsObject(name) {}
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
};
