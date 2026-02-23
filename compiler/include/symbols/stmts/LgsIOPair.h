#pragma once
#include <string>

#include "LgsValue.h"

class LgsFunc;

class LgsIOPair final : public LgsValue {
public:
    std::string openFuncName;
    std::string closeFuncName;
    LgsFunc* openFunc = nullptr;
    LgsFunc* closeFunc = nullptr;

    LgsIOPair(const std::string& openFuncName, const std::string& closeFuncName) : openFuncName(openFuncName), closeFuncName(closeFuncName) {}
    void setDebugValue(LgsCodeGen& cg) override;
};
