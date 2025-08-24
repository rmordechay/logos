#pragma once

class LgsExpr;
class LgsValue;

struct LgsMock {
    LgsValue* when;
    LgsExpr* ret;
    LgsMock(LgsValue* when, LgsExpr* ret) : when(when), ret(ret) {}
};
