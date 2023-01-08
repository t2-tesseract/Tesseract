#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

namespace memory {
    void init();
    void *memmove(void *dest, const void *src, size_t n);
    void *memcpy(char *dst, char *src, int n);
    void* memset(void * ptr, int value, uint16_t num);
    void *malloc(size_t size);
    void free(void *p);
}
