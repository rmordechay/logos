#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include "utils/hashmap.h"

#define SRC_DIR "src"
#define PATH_MAX 1024
#define LOGOS_FILE_EXT "lgs"

/**
 *
 */
typedef struct Application {
    const char *name;
    const char *root_path;
    HashMap *packages;
} App;

/**
 *
 */
typedef struct Package {
    const char *name;
    const char *path;
    HashMap *packages;
    HashMap *files;
} Package;

/**
 *
 */
typedef struct AppFile {
    const char *name;
    const char *path;
    Package *parent;
    const char *code;
} AppFile;


App *init_project();
int is_logos_file(const char *path);

App *create_application(const char *name, const char *root_path);
AppFile *create_app_file(const char *name);
Package *create_package(const char *name, const char *path);

void free_application(App *app);
void free_package(Package *package);
void free_file(AppFile *file);

#endif //PROJECT_H
