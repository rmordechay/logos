#include "project.h"
#include "types/types.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 
 */
void init_project() {
    const char *root_path = "lang/src";
    DIR *root_dir = opendir(root_path);
    App *app = create_application();
    struct dirent *entry;
    char *path = realpath(root_path, NULL);
    app->root_path = path;
    while ((entry = readdir(root_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        const char *name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            char *a = SRC_DIR;
        } else if (entry->d_type == DT_REG) {
            int is_correct_file = is_logos_file(name);
            if (is_correct_file) {
                printf("%s\n", name);
            }
        }
    }
    free_application(app);
}
