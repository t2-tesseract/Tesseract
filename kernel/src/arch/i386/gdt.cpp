#define __GDT__
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include "gdt.hpp"

extern "C" void gdt_flush(uint32_t);
extern "C" void tss_flush();

gdt_entry_t gdt_entries[6];
gdt_ptr_t   gdt_ptr;
tss_entry_t tss_entry;

namespace gdt {
    void set_kernel_stack(uint32_t stack) {
        tss_entry.esp0 = stack;
    }

    static void set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, int gran) {
        gdt_entries[num].base_low    = (base & 0xFFFF);
        gdt_entries[num].base_middle = (base >> 16) & 0xFF;
        gdt_entries[num].base_high   = (base >> 24) & 0xFF;

        gdt_entries[num].limit_low   = (limit & 0xFFFF);
        gdt_entries[num].granularity = (limit >> 16) & 0x0F;
        
        gdt_entries[num].granularity |= gran & 0xF0;
        gdt_entries[num].access      = access;
    }

    static void write_tss(int num, uint16_t ss0, uint32_t esp0) {
        uint32_t base = (uint32_t) &tss_entry;
        uint32_t limit = base + sizeof(tss_entry);

        set_gate(num, base, limit, 0xE9, 0x00);
        memory::memset(&tss_entry, 0, sizeof(tss_entry));

        tss_entry.ss0  = ss0;
        tss_entry.esp0 = esp0;

        tss_entry.cs   = 0x0b;     
        tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
    }

    void init() {
        gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;
        gdt_ptr.base  = (uint32_t)&gdt_entries;

        set_gate(0, 0, 0, 0, 0);
        set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
        set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
        set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
        set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
        write_tss(5, 0x10, 0x0);

        gdt_flush((uint32_t)&gdt_ptr);
        tss_flush();
    }
}