#pragma once

extern "C" void LgsScheduler_init(int hz);
extern "C" void LgsScheduler_shutdown();
extern "C" void LgsScheduler_spawn(void (*task)(void*), void* userdata);
extern "C" void LgsScheduler_run();
extern "C" void LgsScheduler_yield();
