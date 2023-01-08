#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <drivers/video/font.hpp>
#include <common/common.hpp>
#include "isr.hpp"
#include "input.hpp"

static char key_buffer[256];

#define back_space 0x0E
#define enter 0x1C

int keyboard_x;
int keyboard_y;

const char keyboard_map[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b',
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '	\'', '`',   0,
    '	\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/',   0,
    '*',
    0,
    ' ',
    0,
    0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0,   0,   0,
    0,
    0,
    0,
};

namespace keyboard {
    bool backspace(char buffer[]){
        int len = string::strlen(buffer);
        if (len > 0) {
            buffer[len - 1] = '\0';
            return true;
        } else {
            return false;
        }
    }

    void keyboard_handler(registers* r) {
        uint8_t scancode = port::inportb(0x60);

        if (scancode > 57) return;

        if (scancode == 0x0E) {
            if (backspace(key_buffer) == true ) {
                if (keyboard_x < 0){ } else {
                    framebuffer::put_rect(keyboard_x - 8, keyboard_y, 8, 16, 0, 43, 54);
                    framebuffer::flush();
                    keyboard_x -= 8;
                }
            }
            
        } else if (scancode == enter) {
            keyboard_y += 16;
            keyboard_x = 0;
            framebuffer::flush();
        } else {
            char letter = keyboard_map[(int) scancode];
            char string[2] = {letter, '\0'};
            common::append(key_buffer, letter);
            font::put_string(string, keyboard_x, keyboard_y, 255, 255, 255);
            keyboard_x += 8;
            framebuffer::flush();
        }
    }

    void init_keyboard() {
        isr::isr_register_interrupt_handler(IRQ_BASE + 1, keyboard_handler);
    }
}

namespace timer {
    void timer_handler(registers* r) {
        static int tic = 0;
        static int sec = 0;
        tic++;
        if (tic % 10 == 0) {
            sec++;
            tic = 0;
            print_green = 255;
            font::printk(".");
            framebuffer::flush();
        }
    }

    void init_timer() {
        isr::isr_register_interrupt_handler(IRQ_BASE + 0, timer_handler);
    }
}