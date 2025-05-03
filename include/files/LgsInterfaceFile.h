#ifndef LGSINTERFACEFILE_H
#define LGSINTERFACEFILE_H
#include "types/LgsInterface.h"
#include <LgsFile.h>

struct LgsFuncType;

class LgsInterfaceFile final : public LgsFile {
public:
    LgsInterface* interface = nullptr;

    LgsInterfaceFile(const string& name, const string& path) : LgsFile(name, path) {}
    ~LgsInterfaceFile() override = default;
};

#endif //LGSINTERFACEFILE_H
