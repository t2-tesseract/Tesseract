#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "port.hpp"

namespace port {
    void outportb(unsigned short port, unsigned char data) {
        __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
    }

    unsigned char inportb(unsigned short port) {
        unsigned char value;

        __asm__ __volatile__ ("inb %1, %0" : "=a" (value) : "dN" (port));

        return value;
    }

    void outportw(unsigned short port, unsigned short value) {
        asm volatile ("outw %%ax,%%dx": :"dN"(port), "a"(value));
    }
}
