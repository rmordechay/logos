#define TABLE_FIELDS_MAX 1024
#include "logos/LgsCodeGen.h"

struct Lgs_Table_Field {
    const char* name;
    const char* type;
};

struct Lgs_Table {
    size_t len;
    Lgs_Table_Field fields[TABLE_FIELDS_MAX];
};

extern "C" void Lgs_Table_init(Lgs_Table* table) {
    table->len = 0;
}

extern "C" void Lgs_Table_add(Lgs_Table* table, const char* name, const char* type) {
    table->fields[table->len++] = { name, type };
}
