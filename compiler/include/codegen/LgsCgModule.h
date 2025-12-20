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

class LgsCgModule {
public:
    LLVMContext context;
    LgsLLDBGen debugger;
    Module* IRModule = nullptr;
    Function* currentFunc = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    std::map<std::string, Type*> typesRegistry;
    std::unordered_map<std::string, Value*> stringsRegistry;
    bool isRTTModule = false;

    void setupModule(const std::filesystem::path& file, bool debugMode = false);
    bool writeIRModule(const LgsPaths& paths, uint8_t optLevel) const;
    Constant* getString(const std::string& value);
    Value* getPtrTo(Value* v);
    llvm::AllocaInst* getEmptyBuffer();
    GlobalVariable* createGlobal(const std::string& name, Type* type, Constant* initializer, bool isConst = true, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    StructType* getStructType(const std::vector<Type*>& fields, const std::string& name = "");
    void storeStructField(Type* parentType, Value* parentPtr, size_t position, Value* v);
    void store(Value* v, Value* ptr);
    Value* allocaAndStore(Type* type, Value* v);
    void loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body);
    Constant* getRTTypeInfo(const std::string& name, size_t size, Lgs_TypeKind kind, bool isHeapAlloc, Constant* extra);
    Constant* getRTTExtraStruct(const std::string& name, const std::vector<Type*>& fields, const std::vector<Constant*>& args);
    StructType* getRTTBaseStruct();

    // Blocks
    BasicBlock* createBlock(const std::string& name = "", Function* parent = nullptr);
    void branchIfNeeded(BasicBlock* block);
    void startBlock(BasicBlock* block);
    void branchAndStartBlock(BasicBlock* block);
    bool lastInstTerminator() const;
    void createIndexBoundsGuard(Value* len, Value* index);
    void createArrBoundsGuard(Value* maxLen, Value* arrLen);

    // Funcs
    static FunctionType* getFT(Type* rt, const std::vector<Type*>& params = {}, bool isVariadic = false);
    Function* getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    Value* callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {}, bool isVariadic = false);
    Value* callIntrinsics(llvm::Intrinsic::ID intrinsicID, const std::vector<Type*>& types = {}, const std::vector<Value*>& args = {});
    Value* callLgsFunc(const std::string& baseName, const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {});
    Value* callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {}, bool isVariadic = false);

    Value* callPrintf(const std::vector<Value*>& args);
    Value* callSnprintf(const std::string& fmt, const std::vector<Value*>& args);
    Value* callStrLen(Value* str);
    void callMemSet(Value* dest, Value* src, Value* size);
    void callMemCpy(Value* dest, Value* src, Value* size);
    Value* callHash(Value* arg);
    Constant* hashConst(const std::string& str);
    void callThrowError(const LgsBaseMsg& err, const std::vector<Value*>& args = {});
    void freeValue(Value* ptr, Constant* type);
    Value* allocate(Value* size, Constant* type, bool isOwner, bool isReturnExpr = false);

    // Stack
    void callStackPush();
    void callPopStack();
    void addToVTable(Value* instance, Value* key, Value* ptr);
    Value* getFromVTable(Value* instance, Value* key);
    void addNullTerminate(Value* strPtr, Value* pos);

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
    TypeSize typeSize(Type* v) const;
    Value* emptyStr();

    // Debugging
    void printStr(const std::string& str);
    void printPtr(Value* ptr, const std::string& text = "");
    void printInt(Value* number, const std::string& text = "");

    void finalizeDebugger(const std::filesystem::path& buildPath) const;
    llvm::DILocation* getDebugLoc(const LgsLocation& location);
    static void initLLVM();
    static llvm::OptimizationLevel getOptLevel(uint8_t optLevel);
    ~LgsCgModule();
};

inline TargetMachine* targetMachine;
