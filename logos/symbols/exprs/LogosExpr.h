#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H

class LogosExpr {
public:
    std::shared_ptr<LogosTypedValue> value = nullptr;

    explicit LogosExpr() {}
    explicit LogosExpr(const std::shared_ptr<LogosTypedValue>& results) : value(results) {}
    ~LogosExpr() = default;
};

#endif //LOGOSEXPR_H
