#include "project.h"
#include "types/types.h"
#include "analyser/analyser.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct YY_BUFFER_STATE YY_BUFFER_STATE;

void parse(const char *filename);

char* read_file_content(const char *file_path) {
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
    char *content = (char *)malloc(file_size + 1);
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
    // Null-terminate the string
    content[file_size] = '\0';
    fclose(file);
    return content;
}

/**
 * 
 */
void init_project() {
    const char *root_path = realpath("lang/src", NULL);
    DIR *root_dir = opendir(root_path);
    App *app = create_application();
    struct dirent *entry;
    app->root_path = root_path;
    while ((entry = readdir(root_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        const char *name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            char *a = SRC_DIR;
        } else if (entry->d_type == DT_REG) {
            int is_correct_file = is_logos_file(name);
            if (is_correct_file) {
                AppFile *app_file = create_app_file(name);
                char full_path[PATH_MAX];
                snprintf(full_path, sizeof(full_path), "%s/%s", app->root_path, entry->d_name);
                app_file->path = full_path;
                if (strcmp(name, "object.lgs") == 0) {
                    const char *code = read_file_content(app_file->path);
                    app_file->code = code;
                    parse(app_file->code);
                }
            }
        }
    }
    free_application(app);
}
