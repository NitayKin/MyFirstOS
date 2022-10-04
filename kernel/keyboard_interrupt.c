#include "keyboard_interrupt.h"

uint8_t caps_lock_on = 0x00;

void keyboard_int_func(void* x)
{
    __asm__ volatile ("cli");
    char kb_char;
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile("mov %0, al\n\t" // move the char to local variable kb_char;
    : "=r" (kb_char)
    : );
    switch(kb_char)
    {
        case SCANCODE_A:
            if (caps_lock_on)
                print("A",1);
            else
                print("a",1);
            break;
        case SCANCODE_B:
            if (caps_lock_on)
                print("B",1);
            else
                print("b",1);
            break;
        case SCANCODE_C:
            if (caps_lock_on)
                print("C",1);
            else
                print("c",1);
            break;
        case SCANCODE_D:
            if (caps_lock_on)
                print("D",1);
            else
                print("d",1);
            break;
        case SCANCODE_E:
            if (caps_lock_on)
                print("E",1);
            else
                print("e",1);
            break;
        case SCANCODE_F:
            if (caps_lock_on)
                print("F",1);
            else
                print("f",1);
            break;
        case SCANCODE_G:
            if (caps_lock_on)
                print("G",1);
            else
                print("g",1);
            break;
        case SCANCODE_H:
            if (caps_lock_on)
                print("H",1);
            else
                print("h",1);
            break;
        case SCANCODE_I:
            if (caps_lock_on)
                print("I",1);
            else
                print("i",1);
            break;
        case SCANCODE_J:
            if (caps_lock_on)
                print("J",1);
            else
                print("j",1);
            break;
        case SCANCODE_K:
            if (caps_lock_on)
                print("K",1);
            else
                print("k",1);
            break;
        case SCANCODE_L:
            if (caps_lock_on)
                print("L",1);
            else
                print("l",1);
            break;
        case SCANCODE_M:
            if (caps_lock_on)
                print("M",1);
            else
                print("m",1);
            break;
        case SCANCODE_N:
            if (caps_lock_on)
                print("N",1);
            else
                print("n",1);
            break;
        case SCANCODE_O:
            if (caps_lock_on)
                print("O",1);
            else
                print("o",1);
            break;
        case SCANCODE_P:
            if (caps_lock_on)
                print("P",1);
            else
                print("p",1);
            break;
        case SCANCODE_Q:
            if (caps_lock_on)
                print("Q",1);
            else
                print("q",1);
            break;
        case SCANCODE_R:
            if (caps_lock_on)
                print("R",1);
            else
                print("r",1);
            break;
        case SCANCODE_S:
            if (caps_lock_on)
                print("S",1);
            else
                print("s",1);
            break;
        case SCANCODE_T:
            if (caps_lock_on)
                print("T",1);
            else
                print("t",1);
            break;
        case SCANCODE_U:
            if (caps_lock_on)
                print("U",1);
            else
                print("u",1);
            break;
        case SCANCODE_V:
            if (caps_lock_on)
                print("V",1);
            else
                print("v",1);
            break;
        case SCANCODE_W:
            if (caps_lock_on)
                print("W",1);
            else
                print("w",1);
            break;
        case SCANCODE_X:
            if (caps_lock_on)
                print("X",1);
            else
                print("x",1);
            break;
        case SCANCODE_Y:
            if (caps_lock_on)
                print("Y",1);
            else
                print("y",1);
            break;
        case SCANCODE_Z:
            if (caps_lock_on)
                print("Z",1);
            else
                print("z",1);
            break;
        case SCANCODE_SPACE:
            print(" ",1);
            break;
        case SCANCODE_CAPSLOCK:
            caps_lock_on ^= 0x01;
            break;
        case SCANCODE_BACKSPACE:
            break;
        default:
            break;
    }
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al");//tell the PIC its over
}