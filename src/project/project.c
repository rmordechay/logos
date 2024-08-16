#include "project.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 
 */
void init_project() {
    const char *file_extension = "lng";
    const char *root_path = "lang";
    DIR *root_dir = opendir(root_path);
    App *app = create_application();
    struct dirent *entry;
    char *path = realpath(root_path, NULL);
    app->root_path = path;
    while ((entry = readdir(root_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        const char *file_name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            printf("Directory: %s\n", entry->d_name);
        } else if (entry->d_type == DT_REG) {
            char *dot = strrchr(file_name, '.');
            int has_correct_ext = dot && strcmp(dot + 1, file_extension) == 0;
            if (!has_correct_ext) continue;
            printf("File with .%s extension: %s\n", file_extension, entry->d_name);
        }
    }
    free_application(app);
}
