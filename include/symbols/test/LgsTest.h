#pragma once
#include "LgsMock.h"
#include "LgsValue.h"

class LgsTest final : public LgsValue {
public:
    LgsFunc* func;
    std::vector<LgsMock> mocks;

    explicit LgsTest(LgsFunc* func) : func(func) {}
    json::value asJSON() override;
    ~LgsTest() override;
};
