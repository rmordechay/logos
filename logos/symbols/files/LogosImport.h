#ifndef LOGOSIMPORTSTMT_H
#define LOGOSIMPORTSTMT_H
#include "CodeGeneration.h"

class LogosImport final : public CodeGeneration {
public:
    const LogosType* primaryImport;
    LogosType* secondaryImport = nullptr;

    explicit LogosImport(const LogosType* primaryImport) : primaryImport(primaryImport) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stack, Module* module) override;
};

#endif //LOGOSIMPORTSTMT_H
