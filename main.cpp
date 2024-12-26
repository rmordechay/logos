#include "logos/project/LogosProject.h"

int main() {
    const LogosProject project("../lang/src");
    project.scanProject();
    return 0;
}