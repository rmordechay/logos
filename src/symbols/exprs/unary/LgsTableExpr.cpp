#include "exprs/unary/LgsTableExpr.h"
#include "utils/LgsUtils.h"
#include <sqlite3.h>

void LgsTableExpr::createIRValue(LgsCodeGen* codeGen) {
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
}

json::value LgsTableExpr::asJSON() {
    assert(0);
}

std::string LgsTableExpr::pname() {
    return type->pname();
}

LgsTableExpr::~LgsTableExpr() {
    if (tableType) {
        freeType(tableType);
        tableType = nullptr;
    }
}
