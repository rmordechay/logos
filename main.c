#include "project/project.h"
#include "analyser/analysis.h"

int main() {
    App *app = init_project();
    analyse_tree(app);
    free_application(app);
    return 0;
}


