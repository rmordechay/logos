#pragma once
#include "LgsStack.h"
#include <llvm/IR/IRBuilder.h>

class LgsRuntime;
class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

inline mutex mtx;

class LgsCodeGen {
public:
    LgsStack stack;
    LLVMContext context;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    GlobalVariable* runtimePtr = nullptr;
    IRBuilder<> builder = IRBuilder(context);

    void setupModule(const string& moduleName, const DataLayout& dataLayout);
    void setRuntimePtr();
    void callStackPush();
    void callStackPop();
    Value* getIRStr(const string& value);
    GlobalVariable* createGlobal(Type* type, ConstantAggregateZero* zeroInit) const;
    StructType* getStructType(const string& name, const vector<Type*>& fields);

    // Blocks
    BasicBlock* createBlock(const string& name, Function* parent = nullptr);
    void startBlock(BasicBlock* block);
    void branchIfNeeded(BasicBlock* block);
    void branchAndStartBlock(BasicBlock* block);
    bool lastInstTerminator() const;

    // Funcs
    Value* callFunc(const string& funcName, FunctionType* ft, const vector<Value*>& args = {});
    Value* callLgsFunc(const string& funcName, FunctionType* ft, const vector<Value*>& args);
    Value* callMalloc(size_t size);
    Value* callPrintf(const vector<Value*>& args);
    Value* callSnprintf(const vector<Value*>& args);
    Value* callSleep(Value* time);
    Value* callExit(Value* exitCode);
    Value* callGetEnv(Value* name);
    Value* callGetPid();
    Value* callCwd();
    Value* callCoresNum();
    Value* callHashStr(Value* value);
    void callCopyMem(Value* src, Value* dest, size_t n);
    Value* callStrLen(Value* str);

    // Coroutines
    Value* callCoroIDFunc();
    Value* callSuspendFunc();
    Value* callResumeFunc(Value* handle);
    Value* callCoroSizeFunc();
    Value* callCoroBeginFunc(Value* coroID, Value* frameSize);
    Value* callCoroEndFunc(Value* handle);
    Value* callCoroDestroyFunc(Value* handle);

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
    void printPtr(Value* ptr, const string& text);
    void printInt(Value* number, const string& text);
    void printStr(const string& str);

    static void initLLVM();
    ~LgsCodeGen() = default;
};
