#pragma once
#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <map>
#include <filesystem>

#include "exprs/LgsExpr.h"

namespace llvm {
    class DIBuilder;
    class PassBuilder;
    class TargetMachine;
}

using llvm::DIFile;
using llvm::DICompileUnit;
using llvm::DISubprogram;
using llvm::LLVMContext;
using llvm::Module;
using llvm::GlobalVariable;
using llvm::ConstantInt;
using llvm::ConstantAggregateZero;
using llvm::StructType;
using llvm::Constant;
using llvm::GlobalValue;
using llvm::IntegerType;
using llvm::PointerType;
using llvm::TypeSize;
using llvm::FunctionType;
using llvm::Function;
using llvm::BasicBlock;
using llvm::UndefValue;
using llvm::ArrayType;
using llvm::TargetMachine;
using llvm::raw_fd_ostream;
using llvm::DIBasicType;
using llvm::DIBuilder;
using llvm::IRBuilderBase;
using llvm::IRBuilder;
using llvm::Type;
using llvm::Value;
using llvm::Instruction;

struct LgsPaths;
struct LgsAppConfigs;
struct LgsLocation;
struct LgsBaseMsg;
class LgsFile;

struct LgsLLDBGen {
    DIFile* diFile = nullptr;
    DIBuilder* diBuilder = nullptr;
    DICompileUnit* compileUnit = nullptr;
    DISubprogram* subprogram = nullptr;
};

enum LgsCodeGenMode {
    CG_MODE_RTTYPES,
    CG_MODE_SRC_CODE,
    CG_MODE_GENERICS,
};

class LgsCodeGen {
public:
    LgsCodeGenMode mode;
    LLVMContext context;
    LgsLLDBGen debugger;
    Module* IRModule = nullptr;
    Function* currentFunc = nullptr;
    IRBuilder<> builder = IRBuilder(context);
    std::map<std::string, Type*> typesRegistry;
    IRBuilderBase::InsertPoint savedIP;

    explicit LgsCodeGen(const LgsCodeGenMode mode) : mode(mode) {}
    void setupModule(const std::filesystem::path& file, bool debugMode = false);
    bool writeIRModule(const LgsPaths& paths, uint8_t optLevel) const;
    Constant* getString(const std::string& value);
    llvm::AllocaInst* emptyBuffer();
    size_t getAllocSize(Type* type) const;
    GlobalVariable* createGlobal(const std::string& name, Type* type, Constant* initializer, bool isConst = true, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    void loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body);
    void ifStmt(Value* cond, const std::function<void()>& body);
    void ifElseStmt(Value* cond, const std::function<void()>& ifBody, const std::function<void()>& elseBody);

    void store(Value* v, Value* ptr);
    Value* load(Type* ty, Value* ptr);
    Value* loadPtr(Value* value);
    Value* isNull(Value* value);
    void incSize(Value* bufferOffset, Value* ptr);
    Value* allocaAndStore(Type* type, Value* v, const std::string& name = "");
    StructType* getStructType(const std::vector<Type*>& types, const std::string& name = "");
    void storeStructField(Type* parentType, Value* parentPtr, size_t position, Value* v);
    Value* loadStructField(Type* parentType, Value* parentPtr, size_t position, Type* ty);
    void addNullTerminate(Value* strPtr, Value* pos);

    void callStackPush();
    void callPopStack();
    Value* getCurrentLevel();
    Value* callHash(Value* arg);
    Value* getVField(Value* objType, Value* objInstance, Value* fieldName);
    Value* getVFunc(Value* objType, Value* funcName);
    Value* allocInCurrent(Value* size, bool setLevel);
    Value* allocInLevel(Value* size, Value* level, bool setLevel);
    Value* allocStrConst(Value* strPtr);
    Value* reallocate(Value* ptr, Value* size, Value* level);
    Value* moveArrElement(Value* arrLevel, Constant* type, Value* element);
    void throwError(const LgsBaseMsg& err, const std::vector<Value*>& args = {});

    // Blocks
    BasicBlock* createBlock(const std::string& name = "", Function* parent = nullptr);
    void branch(BasicBlock* block);
    void startBlock(BasicBlock* block);
    void branchAndStartBlock(BasicBlock* block);
    Instruction* lastInstTerminator() const;
    void createIndexBoundsGuard(Value* len, Value* index);
    void createArrBoundsGuard(Value* maxLen, Value* arrLen);

    // Funcs
    static FunctionType* getFT(Type* rt, const std::vector<Type*>& params = {}, bool isVariadic = false);
    Function* getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    Value* callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {}, bool isVariadic = false);
    Value* callIntrinsics(llvm::Intrinsic::ID intrinsicID, const std::vector<Type*>& types = {}, const std::vector<Value*>& args = {});
    Value* callLgsFunc(const std::string& baseName, const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {});
    Value* callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {}, bool isVariadic = false);

    // Externals (syscalls, clib, etc.)
    Value* callPrintf(const std::vector<Value*>& args);
    Value* callSnprintf(const std::string& fmt, const std::vector<Value*>& args);
    Value* callStrlen(Value* str);
    Value* strsEqual(Value* str1, Value* str2);
    Value* strsNotEqual(Value* str1, Value* str2);
    void callMemset(Value* dest, Value* src, Value* size);
    void callMemcpy(Value* dest, Value* src, Value* size);

    // Runtime funcs
    GlobalVariable* getRTTypeInfo(const std::string& name, ConstantInt* size, int32_t kind, bool isHeapAlloc, Constant* extra = nullptr);
    StructType* getRTTStruct();

    // Debugging
    void printStr(const std::string& value, const std::string& prefix = "");
    void printStr(Value* value, const std::string& prefix = "");
    void printInt(Value* value, const std::string& prefix = "");
    void printFloat(Value* value, const std::string& prefix = "");
    void printLong(Value* value, const std::string& prefix = "");
    void printPtr(Value* value, const std::string& prefix = "");
    Value* measureTimeStart();
    Value* measureTimeEnd(Value* startTime);

    void finalizeDebugger(const std::filesystem::path& buildPath) const;
    llvm::DILocation* getDebugLoc(const LgsLocation& location);
    static void initLLVM();
    static llvm::OptimizationLevel getOptLevel(uint8_t optLevel);

    // Types
    Type* i1Ty();
    Type* i8Ty();
    Type* i16Ty();
    Type* i32Ty();
    Type* i64Ty();
    Type* floatTy();
    Type* doubleTy();
    Type* voidTy();
    IntegerType* sizeTy();
    PointerType* ptrTy();

    // Values
    Constant* null();
    ConstantInt* true_();
    ConstantInt* false_();
    ConstantInt* i1(bool v);
    ConstantInt* i8(int8_t v);
    ConstantInt* i16(int16_t v);
    ConstantInt* i32(int32_t v);
    ConstantInt* i64(int64_t v);
    ConstantInt* usize(size_t v);
    ConstantInt* zero8();
    ConstantInt* zero32();
    ConstantInt* zero64();
    ConstantInt* zeroSize();
    Value* extendToSize(Value* v);
    Constant* floatv(float_t v);
    Constant* doublev(double_t v);
    Constant* emptyStr();
    ~LgsCodeGen();
};

inline TargetMachine* targetMachine;
