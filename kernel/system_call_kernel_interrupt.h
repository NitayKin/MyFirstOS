#ifndef system_call_interrupt_header
#define system_call_interrupt_header

#include <stdint.h> //for type definitions
#include "print.h"
#include "mutex.h"
#include "scheduler.h"
#include "timer.h"

void system_call_handler(void*) __attribute__((interrupt));

#endif
