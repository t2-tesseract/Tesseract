#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "string.hpp"

namespace string {
    size_t strlen(const char *string) {
        const char *s;

        s = string;
        while (*s)
            s++;
        return (s - string);
    }
}
