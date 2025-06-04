#ifndef LOGOSOBJFILE_H
#define LOGOSOBJFILE_H
#include "LgsFile.h"
#include "types/LgsObject.h"

class LgsObjectFile final : public LgsFile {
public:
    LgsObject *obj = nullptr;

    explicit LgsObjectFile(const string& name, const string& path) : LgsFile(name, path) {}
    Module* generateIR(LogosProject& project) override;
    ~LgsObjectFile() override;
};

#endif //LOGOSOBJFILE_H
