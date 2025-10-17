#pragma once

enum Lgs_rttype {
    RTT_UNKNOWN,
    RTT_VOID,
    RTT_BOOL,
    RTT_CHAR,
    RTT_STR,
    RTT_BYTE,
    RTT_SHORT,
    RTT_INT,
    RTT_LONG,
    RTT_SIZE,
    RTT_UBYTE,
    RTT_USHORT,
    RTT_UINT,
    RTT_ULONG,
    RTT_FLOAT,
    RTT_DOUBLE,
    RTT_VEC2,
    RTT_VEC3,
    RTT_VEC4,
    RTT_SARRAY,
    RTT_DARRAY,
    RTT_SET,
    RTT_MAP,
    RTT_OBJECT,
    RTT_TYPE,
    RTT_ANY,
    RTT_NULLABLE,
};

struct Lgs_vec2 {
    float x, y;
};

struct Lgs_vec3 {
    float x, y, z;
};

struct Lgs_vec4 {
    float x, y, z, w;
};

struct Lgs_nullableInt {
    int32_t v;
    bool isSet;
};