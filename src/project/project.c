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
void visit_file(App *app, const char *name) {
    int is_correct_file = is_logos_file(name);
    if (!is_correct_file) return;
    AppFile *app_file = create_app_file(name);
    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/%s", app->root_path, name);
    app_file->path = full_path;
    app_file->code = read_file_content(app_file->path);
    parse(app_file->code);
    get(app->packages, "");
}

/**
 *
 */
void visit_dir(App *app, const char *path) {
    struct dirent *entry;
    DIR *root_dir = opendir(path);
    while ((entry = readdir(root_dir)) != NULL) {
        int is_dir_valid = strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0;
        if (is_dir_valid) continue;
        const char *name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            Package *pkg = create_package(name);
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, name);
            insert(app->packages, name, pkg);
            visit_dir(app, full_path);
        } else if (entry->d_type == DT_REG) {
            visit_file(app, name);
        }
    }
}

/**
 *
 */
void init_project() {
    const char *root_path = realpath("lang/src", NULL);
    App *app = create_application();
    app->packages = create_hash_map();
    app->root_path = root_path;
    visit_dir(app, app->root_path);
    print_map(app->packages);
    free_application(app);
}
