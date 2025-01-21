#ifndef LOGOSIMPORTSTMT_H
#define LOGOSIMPORTSTMT_H
#include "LogosStmt.h"


class LogosImportStmt final : public LogosStmt {
public:
    const LogosType* primaryImport;
    LogosType* secondaryImport = nullptr;

    explicit LogosImportStmt(const LogosType* primaryImport) : primaryImport(primaryImport) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stack, Module* module) override;
};



#endif //LOGOSIMPORTSTMT_H
