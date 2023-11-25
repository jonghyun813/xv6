#include "types.h"
#include "stat.h"
#include "user.h"

int thread_create(void (*)(void));
void test(void);

int main() {
    void (*func)(void);
    func = &test;
    int cur_pid = getpid();
    int tid, join_pid;
    void **stack;
    
    printf(1, "Spinlock table is initially :\n");
    dummy2();
    t_lock_test(0);
    printf(1, "Spinlock table after lock test is :\n");
    dummy2();


    tid = thread_create(func);
    join_pid = thread_join(stack);
    free(*stack);

    printf(1, "Printing in main thread after thread_join, spinlock table is :\n");
    dummy2();

    exit();
}

void test(void) {
    int pid = getpid();
    printf(1, "Printing in new thread, calling dummy() to change parent's spinlocks\n");
    dummy();

    thread_exit();
}

int thread_create(void (*func)(void)) {
    int tid;
    void *stack = malloc(4096);
    tid = clone((void*)func, (void*)stack);

    return tid;
}
