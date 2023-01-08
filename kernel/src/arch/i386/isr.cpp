#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <common/common.hpp>
#include <drivers/video/font.hpp>
#include "isr.hpp"

_isr g_interrupt_handlers[NO_INTERRUPT_HANDLERS];

char *exception_messages[32] = {
    "Division by zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND range exceeded",
    "Invalid Opcode",
    "Device not available (No Math coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Unknown Interrupt (intel reserved)",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

namespace isr {
    void eoi_pic(uint8_t irq) {
        if(irq >= 0x28)
            port::outportb(PIC2, PIC_EOI);
        port::outportb(PIC1, PIC_EOI);
    }

    void isr_register_interrupt_handler(int num, _isr handler) {
        if (num < NO_INTERRUPT_HANDLERS)
            g_interrupt_handlers[num] = handler;
    }

    void isr_end_interrupt(int num) {
        eoi_pic(num);
    }

    extern "C" void isr_irq_handler(registers *r) {
        if (g_interrupt_handlers[r->int_no] != NULL) {
            _isr handler = g_interrupt_handlers[r->int_no];
            handler(r);
        }
        eoi_pic(r->int_no);
    }

    extern "C" void isr_exception_handler(registers r) {
        if (r.int_no < 32) {
            tasking::close_all_tasks();
            __asm__("cli");
            framebuffer::clear_screen(0, 0, 0);
            font::put_string("FATAL ERROR:", 15, 15, 255, 0, 0);
            font::put_string(exception_messages[r.int_no], 15, 30, 255, 0, 0);

            cursor_y += 48;
            print_red = 255;

            font::printk("  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x",
               r.eax, r.ebx, r.ecx, r.edx, r.esi, r.edi);
            
            font::new_line();

            font::printk("  esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x",
               r.esp, r.ebp, r.eip, r.eflags, r.cs, r.ds, r.ss);
            framebuffer::flush();
            for (;;)
                ;
        }
        if (g_interrupt_handlers[r.int_no] != NULL) {
            _isr handler = g_interrupt_handlers[r.int_no];
            handler(&r);
        }
    }
}