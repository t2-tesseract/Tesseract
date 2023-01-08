#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

namespace port {
    void outportb(unsigned short port, unsigned char data);
    unsigned char inportb(unsigned short port);
    void outportw(unsigned short port, unsigned short value);
}
