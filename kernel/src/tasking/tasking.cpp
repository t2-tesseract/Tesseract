#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "tasking.hpp"

task_t* tasks = NULL;

namespace tasking {
    void add_task(task_t* task) {
        task->next = tasks;
        tasks = task;
    }

    void remove_task(task_t* task) {
        task_t* prev = NULL;
        task_t* curr = tasks;
        while (curr != NULL) {
            if (curr == task) {
            if (prev == NULL) {
                tasks = curr->next;
            } else {
                prev->next = curr->next;
            }
            return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void close_task(task_t* task) {
        remove_task(task);
        memory::free(task->stack);
    }

    void close_all_tasks(void) {
        task_t* task = tasks;

        while (task != NULL) {
            task_t* next = task->next;
            close_task(task);
            task = next;
        }
    }

    void execute_all_tasks(void) {
        task_t* task = tasks;

        while (task != NULL) {
            task_t* next = task->next;
            execute_task(task);
            task = next;
        }
    }

    void configure_task(task_t* task, bool admin, size_t memory, void (*entry)(void)) {
        task->stack = memory::malloc(memory);
        task->entry = entry;
        task->running = false;
        task->admin = admin;

        add_task(task);
    }

    void execute_task(task_t* task) {
        if (!task->admin) {
                // Quit userspace
        }

        if (!task->running) {
            task->running = true;
            task->entry();
            task->running = false;
        }
    }
}
