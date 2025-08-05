#pragma once
#include <files/LgsFile.h>

struct LgsFuncType;

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    LgsInterfaceFile(const string& name, const filesystem::path& path) : LgsFile(name, path) {}
    void generateIR() override;
    ~LgsInterfaceFile() override = default;
};


