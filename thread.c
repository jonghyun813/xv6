#include "types.h"
#include "stat.h"
#include "user.h"

int global_int = 0;
int thread_create(void (*)(void));
void test(void);

int main() {
    void (*func)(void);
    func = &test;
    int pid = getpid();
    int tid;
    
    printf(1, "Printing in PID(%d) : global_int is initially %d\n", pid, global_int);
    tid = thread_create(func);
    sleep(500);

    printf(1, "Printing in PID(%d) : thread_create returned %d\n", pid, tid);
    printf(1, "Printing in PID(%d) : global_int after new thread inreased it by 1 is now %d\n", pid, global_int);
    exit();
}

void test(void) {
    int pid = getpid();

    printf(1, "Printing in PID(%d) : global_int is %d\n", pid, global_int);
    global_int++;
}

int thread_create(void (*func)(void)) {
    int tid;
    void *stack = malloc(4096);
    tid = clone((void*)func, (void*)stack);

    return tid;
}
