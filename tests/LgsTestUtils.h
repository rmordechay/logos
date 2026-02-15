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

inline std::string getLgsOutput(const std::string& code) {
    fs::path execPath = "";
    {
        LgsApp app;
        app.lgsCode = code;
        app.configs.appMode = CODE_MODE;
        const auto success = app.compile();
        EXPECT_TRUE(success);
        if (!success) return "";
        execPath = app.paths.execFile;
    }
    const auto pipe = popen(execPath.c_str(), "r");
    assert(pipe);
    std::string output;
    char buffer[64];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    pclose(pipe);
    return output;
}

inline std::vector<std::string> getLines(std::istringstream& stream, const size_t n) {
    std::vector<std::string> lines;
    for (size_t i = 0; i < n; ++i) {
        std::string line;
        std::getline(stream, line);
        lines.push_back(line);
    }
    return lines;
}