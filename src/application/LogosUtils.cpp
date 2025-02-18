#include "application/LogosUtils.h"

#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "object/LogosField.h"

#include <LogosDefinitions.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosVariable.h>
#include <llvm/Support/FileSystem.h>

using namespace std;

bool Utils::isLogosFile(const filesystem::directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

bool Utils::isMainFile(const filesystem::directory_entry& filePath) {
    return filePath.path().stem().string() == LOGOS_MAIN_FILE;
}