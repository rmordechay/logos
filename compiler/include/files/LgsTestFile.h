#pragma once
#include "LgsFile.h"
#include "funcs/LgsFunc.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsVoid.h"

class LgsTestFile final : public LgsFile {
public:
    std::string name;
    std::vector<LgsFunc*> tests;
    std::vector<LgsFunc*> funcs;
    std::vector<LgsVarDec*> varDecs;
    LgsFunc mockFunc{"mock", &LGS_VOID, {&LGS_ANY, &LGS_ANY}};

    explicit LgsTestFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsTestFile() override;
};
