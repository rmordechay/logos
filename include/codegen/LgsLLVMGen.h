#pragma once
#include "exprs/LgsExpr.h"
#include "logos/LgsApp.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

namespace llvm {
    class TargetMachine;
    class DIBuilder;
}

using namespace llvm;

#define WITH_OWNERSHIP 0

class LgsLLVMGen {
public:
    LLVMContext context;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    DIFile* diFile = nullptr;
    DIBuilder* diBuilder = nullptr;
    DICompileUnit* compileUnit = nullptr;
    DISubprogram* diProgram = nullptr;
    TargetMachine* targetMachine = nullptr;

    void setupModule(const LgsFile& file, bool debugMode = false);
    Value* getIRStr(const std::string& value);
    GlobalVariable* createGlobal(Type* type, ConstantAggregateZero* zeroInit, const std::string& name = "") const;
    GlobalVariable* createConstGlobal(Type* type, Constant* zeroInit, const std::string& name = "") const;
    StructType* getStructType(const std::vector<Type*>& fields, const std::string& name = "");

    // Blocks
    BasicBlock* createBlock(const std::string& name, Function* parent = nullptr);
    void branchIfNeeded(BasicBlock* block);
    void startBlock(BasicBlock* block, Function* func);
    void branchAndStartBlock(BasicBlock* block, Function* func);
    bool lastInstTerminator() const;

    // Funcs
    static FunctionType* getFT(Type* rt, const std::vector<Type*>& params = {}, bool isVariadic = false);
    Function* getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    Value* callFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args = {});
    Value* callLgsFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args = {});

    // System
    Value* callMalloc(size_t size);
    Value* callPrintf(const std::vector<Value*>& args);
    Value* callSleep(Value* time);
    Value* callExit(Value* exitCode);
    Value* callGetEnv(Value* name);
    Value* callGetPid();
    Value* callCwd();
    Value* callCoresNum();
    Value* callStrLen(Value* str);
    Value* callSqrt(Value* radicant);
    void callMemCpy(Value* dest, Value* src, Value* size);
    void callRuntimeInit();

    // Runtime
    void callStackPush();
    void callPopStack();
    void callDefers();
    void addDeferFunc(Value* deferFuncPtr, Value* ctx);
    void addPtrToVtable(Value* instancePtr, Value* name, Value* ptr);
    Value* getPtrFromVtable(Value* instancePtr, Value* name);

    // Coroutines
    void addCoro(Value* coroPtr, Value* ctx);
    void callSpawn(Value* task, Value* ctx);
    void callYield();
    void callShutdown();

    // Internal
    Value* callHashStr(Value* value);

    // Types
    Type* i1Ty();
    Type* i8Ty();
    Type* i16Ty();
    Type* i32Ty();
    Type* i64Ty();
    Type* floatTy();
    Type* doubleTy();
    Type* voidTy();
    Type* iNTy(unsigned n);
    IntegerType* sizeTy();
    PointerType* ptrTy();

    // Values
    Value* null();
    ConstantInt* i1(bool v);
    ConstantInt* i8(int8_t v);
    ConstantInt* i16(int16_t v);
    ConstantInt* i32(int32_t v);
    ConstantInt* i64(int64_t v);
    Constant* floatv(float_t v);
    Constant* doublev(double_t v);
    ConstantInt* usize(size_t v);
    ConstantInt* i32Zero();
    ConstantInt* i64Zero();
    ConstantInt* sizeZero();
    ConstantInt* iN(unsigned size, size_t v);
    TypeSize typeSize(StructType* v) const;
    StructType* getIteratorIRType(const std::string& name);

    // Debugging
    void printStr(const std::string& str);
    void printPtr(Value* ptr, const std::string& text = "");
    void printInt(Value* number, const std::string& text = "");

    static void initLLVM();
    static TargetMachine* getTargetMachine();
    void finalizeDebugger();
};
