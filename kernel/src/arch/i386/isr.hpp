#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <tasking/tasking.hpp>

#define NO_INTERRUPT_HANDLERS    256

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 1)

#define PIC_EOI         0x20

#define ICW1            0x11
#define ICW4_8086       0x01


typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers;

typedef void (*_isr)(registers *);
namespace isr {
    void eoi_pic(uint8_t irq);
    void isr_register_interrupt_handler(int num, _isr handler);
    void isr_end_interrupt(int num);
    extern "C" void isr_irq_handler(registers *reg);
    extern "C" void isr_exception_handler(registers reg);
}

extern "C" void exception_0();
extern "C" void exception_1();
extern "C" void exception_2();
extern "C" void exception_3();
extern "C" void exception_4();
extern "C" void exception_5();
extern "C" void exception_6();
extern "C" void exception_7();
extern "C" void exception_8();
extern "C" void exception_9();
extern "C" void exception_10();
extern "C" void exception_11();
extern "C" void exception_12();
extern "C" void exception_13();
extern "C" void exception_14();
extern "C" void exception_15();
extern "C" void exception_16();
extern "C" void exception_17();
extern "C" void exception_18();
extern "C" void exception_19();
extern "C" void exception_20();
extern "C" void exception_21();
extern "C" void exception_22();
extern "C" void exception_23();
extern "C" void exception_24();
extern "C" void exception_25();
extern "C" void exception_26();
extern "C" void exception_27();
extern "C" void exception_28();
extern "C" void exception_29();
extern "C" void exception_30();
extern "C" void exception_31();
extern "C" void exception_128();

extern "C" void irq_0();
extern "C" void irq_1();
extern "C" void irq_2();
extern "C" void irq_3();
extern "C" void irq_4();
extern "C" void irq_5();
extern "C" void irq_6();
extern "C" void irq_7();
extern "C" void irq_8();
extern "C" void irq_9();
extern "C" void irq_10();
extern "C" void irq_11();
extern "C" void irq_12();
extern "C" void irq_13();
extern "C" void irq_14();
extern "C" void irq_15();

#define IRQ_BASE            0x20
#define IRQ0_TIMER          0x00
#define IRQ1_KEYBOARD       0x01
#define IRQ2_CASCADE        0x02
#define IRQ3_SERIAL_PORT2   0x03
#define IRQ4_SERIAL_PORT1   0x04
#define IRQ5_RESERVED       0x05
#define IRQ6_DISKETTE_DRIVE 0x06
#define IRQ7_PARALLEL_PORT  0x07
#define IRQ8_CMOS_CLOCK     0x08
#define IRQ9_CGA            0x09
#define IRQ10_RESERVED      0x0A
#define IRQ11_RESERVED      0x0B
#define IRQ12_AUXILIARY     0x0C
#define IRQ13_FPU           0x0D
#define IRQ14_HARD_DISK     0x0E
#define IRQ15_RESERVED      0x0F