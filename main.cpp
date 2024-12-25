#include "logos/project/Project.h"

int main() {
    Project project("../lang/src");
    project.scanProject();
    return 0;
}