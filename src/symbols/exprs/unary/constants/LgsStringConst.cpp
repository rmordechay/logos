#include "constants/LgsStringConst.h"

size_t LgsStringConst::size() {
    return value.size();
}

//
// void f() {
//     const auto lc = dynamic_cast<LgsConstant*>(left);
//     const auto rc = dynamic_cast<LgsConstant*>(right);
//     const auto a = get_if<LgsStringConst*>(&lc->value);
//     const auto b = get_if<LgsStringConst*>(&rc->value);
//     auto av = (*b)->value;
//     auto bv = (*a)->value;
//     av.erase(0, 1);
//     av.erase(av.size() - 1);
//     bv.erase(0, 1);
//     bv.erase(bv.size() - 1);
//     const auto c = av + bv;
//     return ConstantDataArray::getString(context, c, true);
// }
