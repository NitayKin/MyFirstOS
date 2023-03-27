#ifndef clock_header
#define clock_header
#include <stdint.h> //for type definitions
#include "print.h"
#include "scheduler.h"
#include "auxility.h"
#include "scheduler.h"

extern uint16_t timer_ticks;
void timer_int_func(void*) __attribute__((interrupt));
void wait_timer_ticks(uint32_t);
void decrease_global_waiting_timer_ticks(void);
#endif
