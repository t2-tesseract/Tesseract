#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "isr.hpp"

#define NO_IDT_DESCRIPTORS 256

typedef struct {
    uint16_t base_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t type;
    uint16_t base_high;
} __attribute__((packed)) _idt;

typedef struct {
    uint16_t limit;
    uint32_t base_address;
} __attribute__((packed)) idt_pointer;

namespace idt {
    void init_pic(void);
    extern "C" void load_idt(uint32_t idt_pointer);
    void set_entry(int index, uint32_t base, uint16_t seg_sel, uint8_t flags);
    void init();
}