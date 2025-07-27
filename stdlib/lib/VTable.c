#include "VTable.h"

void f() {
    void* a[1024];
    int i = 2;
    a[0] = &i;
}
