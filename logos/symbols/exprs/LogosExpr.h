#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H

class LogosExpr {
public:
    LogosTypedValue* results = nullptr;

    explicit LogosExpr() {}
    explicit LogosExpr(LogosTypedValue* results) : results(results) {}
    ~LogosExpr() = default;
};

#endif //LOGOSEXPR_H
