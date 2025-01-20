#ifndef LOGOSOBJFILE_H
#define LOGOSOBJFILE_H
#include "LogosFile.h"
#include "object/LogosObject.h"

class LogosObjectFile final : public LogosFile {
public:

    LogosObject *obj = nullptr;
    explicit LogosObjectFile(const string& name) : LogosFile(name) {}
    static Module* createEmptyModule(const string& name, const IRBuilder<>& builder, const TargetMachine& targetMachine);
    Module* generateModule(const TargetMachine& targetMachine, IRBuilder<>& builder) override;
    ~LogosObjectFile() override = default;
};

#endif //LOGOSOBJFILE_H
