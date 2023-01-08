#include <memory/memory.hpp>
#include <string/string.hpp>
#include <arch/i386/port.hpp>
#include <drivers/video/framebuffer.hpp>

namespace common {
    void itoa(char *buf, unsigned long int n, int base);
    void append(char s[], char n);
}