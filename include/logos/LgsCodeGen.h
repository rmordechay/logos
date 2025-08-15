#pragma once
#include "LgsStack.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Passes/PassBuilder.h>


class LgsFuncCall;
class LgsRuntime;
class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

using namespace llvm;

struct LgsDebug {
    DIFile* diFile = nullptr;
    DIBuilder* diBuilder = nullptr;
    DICompileUnit* compileUnit = nullptr;
    bool isDebug = false;
};

class LgsCodeGen {
public:
    LgsStack stack;
    LLVMContext context;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    LgsDebug debug;

    void setupModule(const std::string& moduleName, const DataLayout& dataLayout);
    Value* getIRStr(const std::string& value);
    GlobalVariable* createGlobal(Type* type, ConstantAggregateZero* zeroInit, const std::string& name = "") const;
    StructType* getStructType(const std::vector<Type*>& fields, const std::string& name = "");
    void storeValueInStruct(StructType* ty, Value* ptr, int i, Value* v);
    Value* loadValueFromStruct(Type* ty, Value* ptr, int i);

    // Blocks
    BasicBlock* createBlock(const std::string& name, Function* parent = nullptr);
    void startBlock(BasicBlock* block);
    void branchIfNeeded(BasicBlock* block);
    void branchAndStartBlock(BasicBlock* block);
    bool lastInstTerminator() const;

    // Funcs
    Function* getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    Value* callFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args = {});
    Value* callLgsFunc(const std::string& funcName, FunctionType* ft, const std::vector<Value*>& args = {});
    Function* getThunkFunc(const LgsFuncCall* fc, Type* ctxTy);
    Value* getThunkCtxValue(const LgsFuncCall* fc, Type* ctxTy);
    Type* getThunkCtxType(const LgsFuncCall* fc);

    // System
    Value* callMalloc(size_t size);
    Value* callPrintf(const std::vector<Value*>& args);
    Value* callSnprintf(const std::vector<Value*>& args);
    Value* callSleep(Value* time);
    Value* callExit(Value* exitCode);
    Value* callGetEnv(Value* name);
    Value* callGetPid();
    Value* callCwd();
    Value* callCoresNum();
    Value* callStrLen(Value* str);
    void callCopyMem(Value* src, Value* dest, size_t n);

    // Stack
    void callStackPush();
    void callPopStack();
    void callDefers();
    void addDeferFunc(Value* deferFuncPtr, Value* ctx);

    // Coroutines
    void addCoro(Value* coroPtr, Value* ctx);
    Value* callCoroIDFunc();
    Value* callSuspendFunc();
    Value* callResumeFunc(Value* handle);
    Value* callCoroSizeFunc();
    Value* callCoroBeginFunc(Value* coroID, Value* frameSize);
    Value* callCoroEndFunc(Value* handle);
    Value* callCoroDestroyFunc(Value* handle);

    // Internal
    Value* callHashStr(Value* value);

    // Types
    Type* i1Ty();
    Type* i8Ty();
    Type* i16Ty();
    Type* i32Ty();
    Type* i64Ty();
    Type* voidTy();
    PointerType* ptrTy();
    Type* iNTy(unsigned n);
    IntegerType* sizeTy();

    // values
    Value* null();
    ConstantInt* i1(bool v);
    ConstantInt* i8(int8_t v);
    ConstantInt* i16(int16_t v);
    ConstantInt* i32(int32_t v);
    ConstantInt* i64(int64_t v);
    ConstantInt* isize(size_t v);
    ConstantInt* i32Zero();
    ConstantInt* i64Zero();
    ConstantInt* sizeZero();
    ConstantInt* iN(unsigned size, size_t v);
    TypeSize typeSize(StructType* v) const;

    // Debugging
    void printPtr(Value* ptr, const std::string& text);
    void printInt(Value* number, const std::string& text);
    void printStr(const std::string& str);

    static void initLLVM();
    ~LgsCodeGen();
};
