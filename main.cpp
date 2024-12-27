#include "logos/project/LogosProject.h"

int main() {
    const LogosProject project("../templates/src");
    project.scanProject();
    return 0;
}