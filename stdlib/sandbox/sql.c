#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *NotUsed, const int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void check_rc(const int rc, char *errMsg) {
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        exit(1);
    }
}

void create_table(sqlite3* db, char* errMsg, int rc) {
    const char *sql_create = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
    rc = sqlite3_exec(db, sql_create, 0, 0, &errMsg);
    check_rc(rc, errMsg);
}

void insert(sqlite3* db, char* errMsg, int rc) {
    const char *sql_insert = "INSERT INTO users (name, age) VALUES ('Alice', 30);";
    rc = sqlite3_exec(db, sql_insert, 0, 0, &errMsg);
    check_rc(rc, errMsg);
}

void select(sqlite3* db, char* errMsg, int rc, const char** sql_select) {
    *sql_select = "SELECT * FROM users;";
    printf("Reading data:\n");
    rc = sqlite3_exec(db, *sql_select, callback, 0, &errMsg);
    check_rc(rc, errMsg);
}

void update(sqlite3* db, char* errMsg, int rc) {
    const char *sql_update = "UPDATE users SET age = 31 WHERE name = 'Alice';";
    rc = sqlite3_exec(db, sql_update, 0, 0, &errMsg);
    check_rc(rc, errMsg);
}

void delete_data(sqlite3* db, char* errMsg, int rc) {
    const char *sql_delete = "DELETE FROM users WHERE name = 'Alice';";
    rc = sqlite3_exec(db, sql_delete, 0, 0, &errMsg);
    check_rc(rc, errMsg);
}

// int main() {
//     sqlite3 *db;
//     char *errMsg = 0;
//     int rc = sqlite3_open("example.db", &db);
//     if (rc) {
//         fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//         return 1;
//     }
//
//     create_table(db, errMsg, rc);
//     insert(db, errMsg, rc);
//     const char* sql_select;
//     select(db, errMsg, rc, &sql_select);
//     update(db, errMsg, rc);
//     select(db, errMsg, rc, &sql_select);
//     delete_data(db, errMsg, rc);
//     sqlite3_close(db);
//     return 0;
// }
