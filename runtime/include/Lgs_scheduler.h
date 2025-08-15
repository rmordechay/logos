#pragma once
#ifdef __cplusplus
extern "C" {
#endif
    void LgsScheduler_init(int hz);
    void LgsScheduler_shutdown();
    void LgsScheduler_spawn(void (*task)(void*), void* userdata);
    void LgsScheduler_run();
    void LgsScheduler_yield();

#ifdef __cplusplus
}
#endif