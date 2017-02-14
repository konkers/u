#ifndef SANDBOX_TASK_H_
#define SANDBOX_TASK_H_

struct task {
    void *coroutine;
}

void task_init(struct task *task, void (*func)(void));
void task_run(struct task *task);

#endif
