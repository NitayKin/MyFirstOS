#include <stdint.h> //for type definitions

#ifndef keyboard_header
#define keyboard_header

void keyboard_int_func(void*) __attribute__((interrupt));
extern uint8_t caps_lock_on;


//scancodes defines:
#define SCANCODE_A 0x1E
#define SCANCODE_B 0x30
#define SCANCODE_C 0x2E
#define SCANCODE_D 0x20
#define SCANCODE_E 0x12
#define SCANCODE_F 0x21
#define SCANCODE_G 0x22
#define SCANCODE_H 0x23
#define SCANCODE_I 0x17
#define SCANCODE_J 0x24
#define SCANCODE_K 0x25
#define SCANCODE_L 0x26
#define SCANCODE_M 0x32
#define SCANCODE_N 0x31
#define SCANCODE_O 0x18
#define SCANCODE_P 0x19
#define SCANCODE_Q 0x10
#define SCANCODE_R 0x13
#define SCANCODE_S 0x1F
#define SCANCODE_T 0x14
#define SCANCODE_U 0x16
#define SCANCODE_V 0x2F
#define SCANCODE_W 0x11
#define SCANCODE_X 0x2D
#define SCANCODE_Y 0x15
#define SCANCODE_Z 0x2C
#define SCANCODE_SPACE 0x39
#define SCANCODE_CAPSLOCK 0x3A
#define SCANCODE_BACKSPACE 0x0E


#endif