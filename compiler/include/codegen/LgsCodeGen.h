#pragma once
#include "Lgs_Types.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <cmath>
#include <map>
#include <filesystem>

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
    LLVMContext context;
    LgsLLDBGen debugger;
    Module* IRModule = nullptr;
    Function* currentFunc = nullptr;
    Value* currentLevel = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    std::map<std::string, Type*> typesRegistry;
    std::unordered_map<std::string, Value*> stringsRegistry;
    LgsCodeGenMode mode = CG_MODE_SRC_CODE;

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
    Value* allocaAndStore(Type* type, Value* v, const std::string& name = "");
    StructType* getStructType(const std::vector<Type*>& types, const std::string& name = "");
    void storeStructField(Type* parentType, Value* parentPtr, size_t position, Value* v);
    Value* loadStructField(Type* parentType, Value* parentPtr, size_t position, Type* ty);
    void addNullTerminate(Value* strPtr, Value* pos);

    void callStackPush();
    void callPopStack();
    Value* callHash(Value* arg);
    void addToVTable(Value* instance, Value* name, Value* ptr);
    Value* getFromVTable(Value* instance, Value* name);
    Value* heapAlloc(Value* size, Value* level, bool withLevel);
    Value* reallocate(Value* ptr, Value* size, Value* level);
    Value* moveElement(Value* iterable, Value* element, Constant* type);
    void callThrowError(const LgsBaseMsg& err, const std::vector<Value*>& args = {});

    // Blocks
    BasicBlock* createBlock(const std::string& name = "", Function* parent = nullptr);
    void createBranch(BasicBlock* block);
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
    Value* callStrLen(Value* str);
    void callMemset(Value* dest, Value* src, Value* size);
    void callMemcpy(Value* dest, Value* src, Value* size);

    // Runtime funcs
    GlobalVariable* getRTTypeInfo(const std::string& name, ConstantInt* size, Lgs_TypeKind kind);
    StructType* getRTTStructType();

    // Debugging
    void printStr(const std::string& value);
    void printStr(Value* value);
    void printInt(Value* value, const std::string& text = "");
    void printLong(Value* value, const std::string& text = "");
    void printPtr(Value* value, const std::string& text = "");
    Value* measureTimeStart();
    void measureTimeEnd(Value* startTime);

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
    ConstantInt* i8Zero();
    ConstantInt* i32Zero();
    ConstantInt* i64Zero();
    ConstantInt* sizeZero();
    Value* extendToSize(Value* v);
    Constant* floatv(float_t v);
    Constant* doublev(double_t v);
    Constant* emptyStr();
    ~LgsCodeGen();
};

inline TargetMachine* targetMachine;
