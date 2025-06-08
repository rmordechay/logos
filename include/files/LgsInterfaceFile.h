#pragma once
#include "types/LgsInterface.h"
#include <files/LgsFile.h>

struct LgsFuncType;

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    LgsInterfaceFile(const string& name, const string& path) : LgsFile(name, path) {}
    ~LgsInterfaceFile() override = default;
};


