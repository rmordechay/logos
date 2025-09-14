#pragma once

class LgsValue;
class LgsExpr;

struct LgsMock {
    LgsValue* when;
    LgsExpr* ret;
    LgsMock(LgsValue* when, LgsExpr* ret) : when(when), ret(ret) {}
};
