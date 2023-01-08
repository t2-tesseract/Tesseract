#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <common/common.hpp>
#include "framebuffer.hpp"

extern int cursor_x, cursor_y;
extern int print_red, print_green, print_blue;

namespace font {
    void put_character(char character, int x, int y, int r, int g, int b);
    void put_string(char* string, int x, int y, int r, int g, int b);
    void printk(char* s, ...);
    void new_line();
}

typedef struct {
    uint8_t magic[2];
    uint8_t mode;
    uint8_t height;
} font_header_t;