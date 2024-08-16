#include <strings.h>
#include <stdlib.h>
#include "utils.h"

/**
 *
 */
void make_http_call() {
    CURL *curl;
    CURLcode res;

    const char *json = "";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) return;
    curl_easy_setopt(curl, CURLOPT_URL, "");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_share_cleanup(headers);
}

/**
 *
 */
void init_string_list(StringList *list, int capacity) {
    list->capacity = capacity;
    list->len = 0;
    list->strings = malloc(capacity * sizeof(char *));
}

/**
 *
 */
void add_to_string(StringList *list, const char *str) {
    if (list->len >= list->capacity) {
        list->capacity *= 2;
        char **new_string = realloc(list->strings, list->capacity * sizeof(char *));
        list->strings = new_string;
    }
    list->strings[list->len] = malloc(strlen(str) + 1);
    strcpy(list->strings[list->len], str);
    list->len++;
}

/**
 *
 */
const char *get_string_element(StringList *list, int i) {
    if (i < 0 || i > list->len) return NULL;
    return list->strings[i];
}

/**
 *
 */
void print_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    printf("User CPU time used: %ld.%06d sec\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System CPU time used: %ld.%06d sec\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    printf("Maximum resident set size: %ld\n", usage.ru_maxrss); // Memory usage in kilobytes
    printf("Integral shared memory size: %ld\n", usage.ru_ixrss);
    printf("Integral unshared data size: %ld\n", usage.ru_idrss);
    printf("Integral unshared stack size: %ld\n", usage.ru_isrss);
    printf("Page reclaims (soft page faults): %ld\n", usage.ru_minflt);
    printf("Page faults (hard page faults): %ld\n", usage.ru_majflt);
    printf("Swaps: %ld\n", usage.ru_nswap);
    printf("Block input operations: %ld\n", usage.ru_inblock);
    printf("Block output operations: %ld\n", usage.ru_oublock);
    printf("IPC messages sent: %ld\n", usage.ru_msgsnd);
    printf("IPC messages received: %ld\n", usage.ru_msgrcv);
    printf("Signals received: %ld\n", usage.ru_nsignals);
    printf("Voluntary context switches: %ld\n", usage.ru_nvcsw);
    printf("Involuntary context switches: %ld\n", usage.ru_nivcsw);
}
