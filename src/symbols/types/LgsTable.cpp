#include "../../../include/symbols/types/LgsTable.h"
#include "builtins/LgsSystem.h"
#include <sqlite3.h>

std::string LgsTable::pname() {
    return getName();
}

llvm::Type* LgsTable::getIRType(LgsCodeGen* codeGen) {
    sqlite3* db;
    char* errMsg;
    sqlite3_open(":memory:", &db);
    constexpr auto createSql = "CREATE TABLE users(id INTEGER PRIMARY KEY, name TEXT);";
    sqlite3_exec(db, createSql, nullptr, nullptr, &errMsg);
    constexpr auto insertSql = "INSERT INTO users(name) VALUES('Alice');";
    sqlite3_exec(db, insertSql, nullptr, nullptr, &errMsg);
    constexpr auto selectSql = "SELECT id, name FROM users;";
    auto callback = [](void*, int argc, char** argv, char** colNames) -> int {
        for (int i = 0; i < argc; i++) {
            std::cout << colNames[i] << "=" << (argv[i] ? argv[i] : "NULL") << " ";
        }
        std::cout << "\n";
        return 0;
    };
    sqlite3_exec(db, selectSql, callback, nullptr, &errMsg);
    constexpr auto updateSql = "UPDATE users SET name='Charlie' WHERE id=1;";
    sqlite3_exec(db, updateSql, nullptr, nullptr, &errMsg);
    constexpr auto deleteSql = "DELETE FROM users WHERE id=2;";
    sqlite3_exec(db, deleteSql, nullptr, nullptr, &errMsg);
    sqlite3_exec(db, selectSql, callback, nullptr, &errMsg);
    sqlite3_close(db);
    return nullptr;
}

size_t LgsTable::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsTable::getZeroValue() {
    assert(0);
}

std::string LgsTable::getName() {
    return name;
}

bool LgsTable::equals(LgsType* other) {
    assert(0);
}

std::string LgsTable::strFormatPart() const {
    return "%s";
}

json::value_ref LgsTable::asJSON() {
    json::object obj;
    return obj;
}
