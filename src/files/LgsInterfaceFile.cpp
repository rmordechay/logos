#include "files/LgsInterfaceFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

LgsInterfaceFile::~LgsInterfaceFile() {
    freeType(interface);
    interface = nullptr;
}
