#include <stddef.h>
#include <stdarg.h>

#include <stdbool.h>
#include <common/common.hpp>

typedef struct task {
  uint32_t* stack;
  void (*entry)(void);
  bool running;
  bool admin;
  struct task* next;
} task_t;

extern task_t* tasks;

namespace tasking {
    void add_task(task_t* task);
    void remove_task(task_t* task);
    void configure_task(task_t* task, bool admin, size_t memory, void (*entry)(void));
    void close_task(task_t* task);
    void close_all_tasks(void);
    void execute_all_tasks(void);
    void execute_task(task_t* task);
}
