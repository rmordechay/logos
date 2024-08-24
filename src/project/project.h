#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include "utils/hashmap.h"

/**
 *
 */
typedef struct Application {
    char *name;
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
    const char *parent_path;
    const char *code;
} AppFile;


void init_project();
int is_logos_file(const char *path);

App *create_application(const char *root_path);
AppFile *create_app_file(const char *name);
Package *create_package(const char *name, const char *path);

void free_application(App *app);
void free_package(Package *package);
void free_file(AppFile *file);

#endif //PROJECT_H
