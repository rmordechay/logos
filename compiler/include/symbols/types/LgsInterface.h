#pragma once
#include "LgsObject.h"
#include "LgsType.h"

class LgsInterface final : public LgsObject {
public:
    explicit LgsInterface(const std::string& name) : LgsObject(name) {}
    bool canCastTo(LgsType* other) override;
};
