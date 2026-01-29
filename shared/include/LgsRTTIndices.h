#pragma once

struct Lgs_StrIndices {
    const size_t level = 0;
    const size_t data = 1;
};

struct Lgs_HashMapIndices {
    const size_t level = 0;
    const size_t type = 1;
    const size_t entries = 2;
    const size_t len = 3;
    const size_t cap = 4;
    const size_t key = 0;
    const size_t value = 1;
    const size_t next = 2;
};

struct Lgs_DArrayExprIndices {
    const size_t level = 0;
    const size_t type = 1;
    const size_t data = 2;
    const size_t len = 3;
    const size_t cap = 4;
};

struct Lgs_ObjectIndices {
    const size_t id = 0;
    const size_t name = 1;
    const size_t size = 2;
    const size_t fieldsCount = 3;
    const size_t funcsCount = 4;
    const size_t fields = 5;
    const size_t funcs = 6;
};

struct Lgs_InstanceIndices {
    const size_t level = 0;
    const size_t type = 1;
};
