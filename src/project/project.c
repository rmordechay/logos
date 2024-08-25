#include "project.h"
#include "utils/hashmap.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SRC_DIR "src"
#define PATH_MAX 1024

typedef struct YY_BUFFER_STATE YY_BUFFER_STATE;
void parse(const char *filename);

char *read_file_content(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }
    // Seek to the end of the file to determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    // Allocate memory for the content + null terminator
    char *content = (char *) malloc(file_size + 1);
    if (content == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }
    // Read the file into the buffer
    size_t read_size = fread(content, 1, file_size, file);
    if (read_size != file_size) {
        perror("Failed to read file");
        free(content);
        fclose(file);
        return NULL;
    }
    // Null-terminate string
    content[file_size] = '\0';
    fclose(file);
    return content;
}

/**
 *
 */
void visit_file(Package *package, const char *file_name, const char *file_path) {
    int is_correct_file = is_logos_file(file_name);
    if (!is_correct_file) return;
    AppFile *app_file = create_app_file(file_path);
    app_file->path = file_path;
    app_file->name = file_name;
    app_file->code = read_file_content(app_file->path);
    put_in_map(package->files, file_name, app_file);
}

/**
 *
 */
void visit_package(Package *package) {
    struct dirent *entry;
    DIR *dir = opendir(package->path);
    while ((entry = readdir(dir)) != NULL) {
        int is_dir_valid = strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0;
        if (is_dir_valid) continue;
        const char *file_or_dir_name = entry->d_name;
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", package->path, file_or_dir_name);
        if (entry->d_type == DT_DIR) {
            Package *child_pkg = create_package(file_or_dir_name, path);
            put_in_map(package->packages, file_or_dir_name, child_pkg);
            visit_package(child_pkg);
        } else if (entry->d_type == DT_REG) {
            visit_file(package, file_or_dir_name, path);
        }
    }
}

/**
 *
 */
App *init_project() {
    const char *root_path = realpath("lang/src", NULL);
    App *app = create_application(root_path);
    Package *root_package = create_package(SRC_DIR, root_path);
    put_in_map(app->packages, SRC_DIR, root_package);
    visit_package(root_package);
    return app;
}
