#include "types.h"
#include "stat.h"
#include "user.h"

int global_int = 0;
int thread_create(void (*)(void));
void test(void);

int main() {
    void (*func)(void);
    func = &test;
    int cur_pid = getpid();
    int tid, join_pid;
    void **stack;
    
    printf(1, "Printing in PID(%d) : global_int is initially %d\n", cur_pid, global_int);

    tid = thread_create(func);
    join_pid = thread_join(stack);
    printf(1, "Printing in PID(%d) : thread_create returned %d\n", cur_pid, tid);
    printf(1, "Printing in PID(%d) : thread_join returned %d\n", cur_pid, join_pid);

    printf(1, "stack address in main : %d\n", *stack);
    free(*stack);

    printf(1, "Printing in PID(%d) : global_int after new thread increased it by 1 is now %d\n", cur_pid, global_int);
    exit();
}

void test(void) {
    int pid = getpid();

    printf(1, "Printing in PID(%d) : global_int currently %d, this function will increment this by 1\n", pid, global_int, global_int+1);
    global_int++;
    thread_exit();
}

int thread_create(void (*func)(void)) {
    int tid;
    void *stack = malloc(4096);
    printf(1, "stack address in thread_create : %d\n", stack);
    tid = clone((void*)func, (void*)stack);

    return tid;
}
