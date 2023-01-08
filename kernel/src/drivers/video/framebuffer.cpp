#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <common/common.hpp>
#include <multiboot/boot.hpp>
#include "framebuffer.hpp"

namespace framebuffer {
    void put_pixel(int x, int y, int r, int g, int b) {
        // unsigned *buffer = (unsigned *)(mb_info->framebuffer_addr + y * mb_info->framebuffer_pitch);
        // buffer[x] = (r << 16) | (g << 8) | b;
        unsigned *backbuffer = (unsigned *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
        backbuffer[x] = (r << 16) | (g << 8) | b;
    }

    void put_hexadecial(int x, int y, unsigned int color) {
        unsigned *backbuffer = (unsigned *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
        backbuffer[x] = color;
    }

    void clear_screen(int r, int g, int b) {
        for(unsigned y = 0; y < mb_info->framebuffer_height; ++y) {
            for(unsigned x = 0; x < mb_info->framebuffer_width; ++x)
                put_pixel(x, y, r, g, b);
        }
    }

    void put_rect(int x, int y, int width, int height, int r, int g, int b) {
        for (int j = y; j < (y + height); j++) {
            for (int i = x; i < (x + width); i++) {
                put_pixel(i, j, r, g, b);
            }
        }
    }

    void flush() {
        memory::memcpy(mb_info->framebuffer_addr, mb_info->framebuffer_addr + mb_info->framebuffer_height * mb_info->framebuffer_pitch, mb_info->framebuffer_pitch * mb_info->framebuffer_height);
    }
}