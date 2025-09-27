#pragma once
#include "LgsValue.h"

class LgsIOPair final : public LgsValue {
public:
    std::string openFuncName;
    std::string closeFuncName;
    LgsFunc* openFunc = nullptr;
    LgsFunc* closeFunc = nullptr;

    LgsIOPair(const std::string& openFuncName, const std::string& closeFuncName) : openFuncName(openFuncName), closeFuncName(closeFuncName) {}
    json::value asJsonStr() override;
};
