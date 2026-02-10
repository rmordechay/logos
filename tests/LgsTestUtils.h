#pragma once
#include "logos/LgsApp.h"
#include "gtest/gtest.h"
#include "errors/LgsErrors.h"

inline void expectErrors(const LgsApp& app, const LgsBaseMsg& baseMsg, const size_t n) {
    EXPECT_EQ(app.errHandler.errors.size(), n) << EXPECTED_ERR(baseMsg);
    if (app.errHandler.errors.size() <= 0) return;
    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(app.errHandler.errors[i].errCode, baseMsg.errCode);
    }
}