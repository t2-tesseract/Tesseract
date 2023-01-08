// #include <stddef.h>
// #include <stdarg.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <drivers/video/font.hpp>
// #include <common/common.hpp>
// #include "isr.hpp"
// #include "input.hpp"

// namespace timer {
//     void timer_handler(registers* r) {
//         static int tic = 0;
//         static int sec = 0;
//         tic++;
//         if (tic % 10 == 0) {
//             sec++;
//             tic = 0;
//             print_green = 255;
//             font::printk(".");
//             framebuffer::flush();
//         }
//     }

//     void init_timer() {
//         isr::isr_register_interrupt_handler(IRQ_BASE + 0, timer_handler);
//     }
// }