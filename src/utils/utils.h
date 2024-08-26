#include <strings.h>
#include <stdlib.h>
#include <curl/curl.h>

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


