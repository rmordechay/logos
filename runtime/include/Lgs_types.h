#pragma once

enum LgsRTType {
    RTT_UNKNOWN,
    RTT_VOID,
    RTT_BOOL,
    RTT_CHAR,
    RTT_STR,
    RTT_FLOAT,
    RTT_INT,
    RTT_VEC2,
    RTT_VEC3,
    RTT_VEC4,
};

struct Vec2 {
    float x, y;
};

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

