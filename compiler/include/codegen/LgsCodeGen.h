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
struct LgsLLDBGen {
    DIFile* diFile = nullptr;
    DIBuilder* diBuilder = nullptr;
    DICompileUnit* compileUnit = nullptr;
    DISubprogram* subprogram = nullptr;
};
struct LgsPaths;
struct LgsAppConfigs;
struct LgsLocation;
struct LgsBaseMsg;
class LgsFile;

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
    Constant* getString(const std::string& value, bool addNull = true);
    GlobalVariable* createGlobal(const std::string& name, Type* type, Constant* initializer, bool isConst = true, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    void loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body);
    void ifStmt(Value* cond, const std::function<void()>& body);
    void ifElseStmt(Value* cond, const std::function<void()>& ifBody, const std::function<void()>& elseBody);

    void store(Value* v, Value* ptr);
    Value* load(Type* ty, Value* ptr);
    Value* loadPtr(Value* value);
    Value* loadSize(Value* value);
    Value* isNull(Value* value);
    Value* getLevel(Value* v);
    Value* emptyBuffer(size_t size = 0);
    void incSize(Value* bufferOffset, Value* ptr);
    void addNullTerminate(Value* strPtr, Value* pos);
    Value* allocaAndStore(Type* type, Value* v, const std::string& name = "");
    Value* loadField(Type* parentType, Value* parentPtr, size_t position, Type* ty);
    void storeField(Type* parentType, Value* parentPtr, size_t position, Value* v);
    StructType* getStructType(const std::vector<Type*>& types, const std::string& name = "");

    void callStackPush();
    void callPopStack();
    Value* getCurrentLevel();
    Value* callHash(Value* type, Value* arg);
    Value* getVField(Value* objType, Value* objInstance, Value* fieldName);
    Value* getVFunc(Value* objType, Value* funcName);
    Value* allocInCurrent(Value* size, bool setLevel);
    Value* allocInLevel(Value* size, Value* level, bool setLevel);
    Value* allocStr(Value* strPtr);
    Value* allocEmptyStr(Value* length);
    Value* reallocate(Value* ptr, Value* size, Value* level);
    Value* moveValue(const std::string& baseName, Value* v, Value* toLevel);
    void throwError(const LgsBaseMsg& err, const std::vector<Value*>& args = {});

    // Blocks
    BasicBlock* createBlock(const std::string& name = "", Function* parent = nullptr);
    void startFunc(Function* parent = nullptr);
    void branch(BasicBlock* block);
    void startBlock(BasicBlock* block);
    void branchAndStartBlock(BasicBlock* block);
    Instruction* lastInstTerminator() const;
    void assertGuard(Value* cond);
    void createNullPtrGuard(Value* value);
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
    Value* callPrintf(const std::string& fmt, const std::vector<Value*>& args);
    Value* callSnprintf(const std::string& fmt, const std::vector<Value*>& args);
    Value* callSnprintf(const std::string& fmt, Value* buffer, Value* size, Value* ptr);
    Value* callStrlen(Value* str);
    Value* strsEqual(Value* str1, Value* str2);
    Value* strsNotEqual(Value* str1, Value* str2);
    void callMemset(Value* dest, Value* src, Value* size);
    void callMemcpy(Value* dest, Value* src, Value* size);

    StructType* getRTTStruct();

    // Debugging
    void printStr(const std::string& value, const std::string& prefix = "");
    void printStr(Value* value, const std::string& prefix = "");
    void printInt(Value* value, const std::string& prefix = "");
    void printFloat(Value* value, const std::string& prefix = "");
    void printLong(Value* value, const std::string& prefix = "");
    void printPtr(Value* value, const std::string& prefix = "");
    void printBytes(Value* value, Value* size, const std::string& prefix = "");
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
    ConstantInt* getTypeSize(Type* ty);

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
    Constant* floatv(float_t v);
    Constant* doublev(double_t v);
    ConstantInt* zero8();
    ConstantInt* zero32();
    ConstantInt* zero64();
    ConstantInt* zeroSize();
    Value* toFloat(Value* v);
    Value* toInt(Value* v);
    Value* toSize(Value* v);
    Constant* emptyStr();
    ~LgsCodeGen();
};

class LgsStrBuilder {
public:
    Value* index;
    Value* buffer;
    LgsCodeGen& cg;
    bool asJSON = false;

    explicit LgsStrBuilder(LgsCodeGen& cg, Value* buffer = nullptr) : cg(cg) {
        this->buffer = buffer ? buffer : cg.emptyBuffer();
        index = cg.allocaAndStore(cg.sizeTy(), cg.zeroSize());
    }
    void add(Value* value, Value* size) const;
    void add(const std::string& value) const;
    void finalize() const;
};
