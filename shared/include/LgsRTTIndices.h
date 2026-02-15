#pragma once

struct LgsTypeInfoIndices {
    static constexpr size_t name = 0;
    static constexpr size_t size = 1;
    static constexpr size_t kind = 2;
    static constexpr size_t isHeap = 3;
    static constexpr size_t extra = 4;
};

struct LgsStrIndices {
    static constexpr size_t level = 0;
    static constexpr size_t data = 1;
};

struct LgsHashMapIndices {
    static constexpr size_t level = 0;
    static constexpr size_t type = 1;
    static constexpr size_t entries = 2;
    static constexpr size_t length = 3;
    static constexpr size_t cap = 4;
    static constexpr size_t key = 0;
    static constexpr size_t value = 1;
    static constexpr size_t next = 2;
};

struct LgsDArrExprIndices {
    static constexpr size_t level = 0;
    static constexpr size_t baseType = 1;
    static constexpr size_t length = 2;
    static constexpr size_t capacity = 3;
    static constexpr size_t data = 4;
};

struct LgsObjIndices {
    static constexpr size_t id = 0;
    static constexpr size_t name = 1;
    static constexpr size_t size = 2;
    static constexpr size_t fieldsCount = 3;
    static constexpr size_t funcsCount = 4;
    static constexpr size_t fields = 5;
    static constexpr size_t funcs = 6;
};

struct LgsFieldIndices {
    static constexpr size_t name = 0;
    static constexpr size_t size = 1;
    static constexpr size_t offset = 2;
    static constexpr size_t kind = 3;
    static constexpr size_t type = 4;
};

struct LgsMethodIndices {
    static constexpr size_t name = 0;
    static constexpr size_t ptr = 1;
};

struct LgsInstanceIndices {
    static constexpr size_t level = 0;
    static constexpr size_t type = 1;
};

struct LgsNullableExprIndices {
    static constexpr size_t value = 0;
    static constexpr size_t isSet = 1;
};

