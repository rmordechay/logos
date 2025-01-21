#ifndef LOGOSOBJFILE_H
#define LOGOSOBJFILE_H
#include "LogosFile.h"
#include "object/LogosObject.h"

class LogosObjectFile final : public LogosFile {
public:
    LogosObject *obj = nullptr;

    explicit LogosObjectFile(const string& name) : LogosFile(name) {}
    Module* generateModule(IRBuilder<>& builder, LogosStack& theStack) override;
    void initModule(IRBuilder<>& builder, LogosStack& theStack) override;
    ~LogosObjectFile() override;
};

#endif //LOGOSOBJFILE_H
