#pragma once
#include "LgsStack.h"

class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

inline TargetMachine* targetMachine = nullptr;
inline mutex mtx;

class LgsCodeGen {
public:
    LgsStack stack;
    LLVMContext context;
    Value* pathIR = nullptr;
    off_t filePathIndex = 0;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);

    void createIRModule(const string& moduleName);
    Value* getIRStr(const string& value);
    StructType* getIRStructType(const string& name, const vector<Type*>& fields);
    GlobalVariable* createIRGlobal(Type* type, Constant* value) const;
    bool lastInstTerminator() const;

    void branchToBlock(BasicBlock* block);
    void startBlock(BasicBlock* block);
    void startFuncBlock();

    Value* callPrintf(const vector<Value*>& args);
    Value* callSnprintf(const vector<Value*>& args);
    Value* callStrHash(Value* value);
    void callCopyMem(Value* src, Value* dest, size_t n);

    Value* callFunc(const string& funcName, FunctionType* ft, const vector<Value*>& args = {});
    void callPushStack(off_t pathIndex);
    void callPrintError(const string& msg);
    void callInitRuntime();
    void callPopStack();
    Value* callIDFunc();
    Value* callSuspendFunc();
    Value* callResumeFunc(Value* handle);
    Value* callSizeFunc();
    Value* callBeginFunc(Value* coroID, Value* frameSize);
    Value* callEndFunc(Value* handle);
    Value* callDestroyFunc(Value* handle);

    Type* i1Ty();
    Type* i8Ty();
    Type* i16Ty();
    Type* i32Ty();
    Type* i64Ty();
    Type* voidTy();
    PointerType* ptrTy();
    IntegerType* sizeTy();
    ConstantInt* i1(bool v);
    ConstantInt* i8(int8_t v);
    ConstantInt* i16(int16_t v);
    ConstantInt* i32(int32_t v);
    ConstantInt* i64(int64_t v);
    ConstantInt* size(size_t v);
    ConstantInt* i32Zero();
    ConstantInt* i64Zero();
    ConstantInt* sizeZero();
    Value* null();

    static void initLLVM();
    static TargetMachine* getTargetMachine();
    ~LgsCodeGen() = default;
};

inline map<string, LgsFile*> externalFiles;
