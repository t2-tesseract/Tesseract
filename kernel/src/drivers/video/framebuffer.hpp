#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

namespace framebuffer {
    void put_pixel(int x, int y, int r, int g, int b);
    void put_hexadecial(int x, int y, unsigned int color);
    void clear_screen(int r, int g, int b);
    void put_rect(int x, int y, int width, int height, int r, int g, int b);
    void flush();
}