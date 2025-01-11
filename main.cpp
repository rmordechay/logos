#include "logos/project/LogosProject.h"

int main() {
    LogosProject project("../templates/src");
    project.scanProject();
    return 0;
}