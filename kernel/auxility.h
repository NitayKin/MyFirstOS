#ifndef auxility_header
#define auxility_header

#include "print.h"
#include <stdint.h> //for type definitions


#define out(port,value) \
__asm__ volatile("push eax"); \
__asm__ volatile("push edx"); \
__asm__ volatile("mov dx, %0"::"r"((uint16_t)port)); \
__asm__ volatile("mov al, %0"::"r"((uint8_t)value)); \
__asm__ volatile("out dx, al"); \
__asm__ volatile("pop edx"); \
__asm__ volatile("pop eax");

#define PRINT_ESP() \
uint32_t my_esp;\
__asm__ volatile ("mov %0, esp":"=r" (my_esp));\
 print_hex(&my_esp,4);

#define PRINT_EBP() \
uint32_t my_ebp;\
__asm__ volatile ("mov %0, ebp":"=r" (my_ebp));\
 print_hex(&my_ebp,4);

#define PRINT_EIP()\
uint32_t my_eip;\
__asm__ volatile ("Call $+5");\
__asm__ volatile ("pop %0":"=r" (my_eip));\
print_hex(&my_eip,4);

#define PUSH_GENERAL_REG_NO_EAX()\
__asm__ volatile ("push ebx");\
__asm__ volatile ("push ecx");\
__asm__ volatile ("push edx");

#define POP_GENERAL_REG_NO_EAX()\
__asm__ volatile ("pop edx");\
__asm__ volatile ("pop ecx");\
__asm__ volatile ("pop ebx");


#endif
